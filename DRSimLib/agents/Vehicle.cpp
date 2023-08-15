#include "include/drsim/Vehicle.h"
#include "events/ArcEndEvent.h"
#include "events/RepositioningArrivalEvent.h"
#include "events/RepositioningUpdateEvent.h"
#include "events/ServiceEndEvent.h"
#include "events/ServiceStartEvent.h"
#include "events/TourStopArrivalEvent.h"
#include "events/TourUpdateEvent.h"
#include "include/drsim/Engine.h"
#include "include/drsim/PlanningServiceInterface.h"
#include "include/drsim/RoutingEngineInterface.h"
#include "include/drsim/SimulationStats.h"
#include "spdlog/spdlog.h"
#include "utility/TimeUtil.h"

namespace drsim {
Vehicle::Vehicle(const VehicleData& vehicleData, PlanningServiceInterface& planningService,
                 RoutingEngineInterface& routingEngine, Engine& engine, SimulationStats& simulationStats)
    : vehicleData(vehicleData)
    , planningService(planningService)
    , routingEngine(routingEngine)
    , engine(engine)
    , simulationStats(simulationStats)
    , state(VehicleState::IDLE)
    , currentLocation(vehicleData.getLocation())
    , tour()
    , route()
    , arc()
    , serviceEndTime()
    , repositioningTarget()
    , pendingTourUpdate()
    , pendingRepositioningUpdate()
    , pendingVehicleAction() {
    this->planningService.get().createVehicle(engine.getTime(), vehicleData.getLocation(), vehicleData.getCapacity(),
                                              vehicleData.getId());
    this->simulationStats.get().addVehicleStats(vehicleData);
    this->simulationStats.get().addVehicleMovement(
        vehicleData.getId(), VehicleMovementLogEntry(vehicleData.getId(), this->engine.get().getTime(),
                                                     this->engine.get().getTime(), currentLocation, currentLocation));
    this->simulationStats.get().changeVehicleState(vehicleData.getId(), state, this->engine.get().getTime());
}

PointLatLon Vehicle::getLocation() const {
    if (!arc) {
        return currentLocation;
    }
    return arc->getLocationAtTime(engine.get().getTime());
}

int Vehicle::getId() const {
    return vehicleData.getId();
}

void Vehicle::assignTour(const std::vector<TourStop>& tour) {
    spdlog::info("Assigning tour to vehicle {}", vehicleData.getId());
    if (pendingTourUpdate || hasFirstStopChanged(tour)) {
        std::unique_ptr<Event> event =
            std::make_unique<TourUpdateEvent>(engine.get().getTime(), getUpdateEventExecutionTime(), *this, tour);
        cancelPendingVehicleAction();
        cancelPendingRepositioningUpdate();
        cancelPendingTourUpdate();
        pendingTourUpdate.emplace(engine.get().add(event));
        storeStateIfChanged(VehicleState::ACTIVE);
    } else {
        this->tour = tour;
    }
}

void Vehicle::assignRepositioning(const PointLatLon& target) {
    spdlog::info("Repositioning vehicle {} to {}", vehicleData.getId(), target.toString());
    std::unique_ptr<Event> event = std::make_unique<RepositioningUpdateEvent>(
        engine.get().getTime(), getUpdateEventExecutionTime(), *this, target);
    cancelPendingRepositioningUpdate();
    cancelPendingVehicleAction();
    pendingRepositioningUpdate.emplace(engine.get().add(event));
    storeStateIfChanged(VehicleState::REPOSITIONING);
}

void Vehicle::updateTour(const std::vector<TourStop>& tour) {
    pendingTourUpdate.reset();
    repositioningTarget.reset();
    route.reset();
    arc.reset();
    this->tour = tour;
    moveToNextTarget();
}

void Vehicle::updateRepositioning(const PointLatLon& target) {
    if (!tour.empty()) {
        throw std::exception("Cannot reposition active vehicle");
    }
    pendingRepositioningUpdate.reset();
    repositioningTarget = target;
    moveToNextTarget();
}

void Vehicle::moveToNextTarget() {
    if (hasTarget()) {
        PointLatLon currentLocation = getLocation();
        PointLatLon target = tour.empty() ? repositioningTarget.value() : tour.at(0).getLocation();
        route.emplace(routingEngine.get().calculateRoute(currentLocation, target, engine.get().getTime()));
        scheduleArrivalEvent();
        moveToNextArc();
        spdlog::info("Routing vehicle {} to {} in {} seconds", vehicleData.getId(), target.toString(),
                     route.value().getDuration().total_seconds());
    }
}

void Vehicle::moveToNextArc() {
    if (route) {
        arc.emplace(route.value().popArc());
        planningService.get().updateNextRoutableLocation(engine.get().getTime(), arc.value().getEndLocation(),
                                                         arc.value().getEndTime(), vehicleData.getId());
        std::unique_ptr<Event> event =
            std::make_unique<ArcEndEvent>(engine.get().getTime(), arc.value().getEndTime(), *this, arc.value());
        engine.get().add(event);
        simulationStats.get().addVehicleMovement(
            vehicleData.getId(),
            VehicleMovementLogEntry(vehicleData.getId(), engine.get().getTime(), arc.value().getEndTime(),
                                    arc.value().getStartLocation(), arc.value().getEndLocation()));
        spdlog::debug("Moving vehicle {} to the next arc with target {}", vehicleData.getId(),
                      arc.value().getEndLocation().toString());
    }
}

void Vehicle::endArc(const RouteArc& arc) {
    currentLocation = arc.getEndLocation();
    this->arc.reset();
    if (!isUpdatePending() && !route.value().getArcs().empty()) {
        moveToNextArc();
    }
}

void Vehicle::scheduleArrivalEvent() {
    std::unique_ptr<Event> event;
    const auto arrivalTime = engine.get().getTime() + route.value().getDuration();
    if (!tour.empty()) {
        event = std::make_unique<TourStopArrivalEvent>(engine.get().getTime(), arrivalTime, *this);
    } else {
        event = std::make_unique<RepositioningArrivalEvent>(engine.get().getTime(), arrivalTime, *this);
    }
    pendingVehicleAction.emplace(engine.get().add(event));
}

void Vehicle::arriveAtTourStop() {
    const auto& tourStop = tour.at(0);
    pendingVehicleAction.reset();
    route.reset();
    std::unique_ptr<Event> event = std::make_unique<ServiceStartEvent>(
        engine.get().getTime(), maxDateTime(tourStop.getEarliestTime(), engine.get().getTime()), *this);
    pendingVehicleAction.emplace(engine.get().add(event));
    spdlog::debug("Vehicle {} arrives at tour stop for request {}", vehicleData.getId(), tourStop.getRequestId());
}

void Vehicle::startService() {
    const auto& tourStop = tour.at(0);
    logServiceEvent(tourStop, true);
    pendingVehicleAction.reset();
    if (tourStop.getAction() == TourStopAction::PICKUP) {
        planningService.get().startPickup(engine.get().getTime(), vehicleData.getId(), tourStop.getRequestId());
        simulationStats.get().pickupRequest(tourStop.getRequestId(), engine.get().getTime());
    } else {
        planningService.get().startDropoff(engine.get().getTime(), vehicleData.getId(), tourStop.getRequestId());
    }
    serviceEndTime.emplace(engine.get().getTime() + tourStop.getServiceDuration());
    std::unique_ptr<Event> event =
        std::make_unique<ServiceEndEvent>(engine.get().getTime(), serviceEndTime.value(), *this);
    engine.get().add(event);
}

void Vehicle::endService() {
    const auto& tourStop = tour.at(0);
    logServiceEvent(tourStop, false);
    if (tourStop.getAction() == TourStopAction::PICKUP) {
        planningService.get().endPickup(engine.get().getTime(), vehicleData.getId(), tourStop.getRequestId());
    } else {
        planningService.get().endDropoff(engine.get().getTime(), vehicleData.getId(), tourStop.getRequestId());
        simulationStats.get().dropoffRequest(tourStop.getRequestId(), engine.get().getTime());
    }
    tour.erase(tour.begin());
    serviceEndTime.reset();
    if (tour.empty()) {
        storeStateIfChanged(VehicleState::IDLE);
    }
    moveToNextTarget();
}

void Vehicle::arriveAtRepositioning() {
    spdlog::info("Finished repositioning for vehicle {}", vehicleData.getId());
    pendingVehicleAction.reset();
    route.reset();
    repositioningTarget.reset();
    planningService.get().finishRepositioning(engine.get().getTime(), vehicleData.getId());
    storeStateIfChanged(VehicleState::IDLE);
}

void Vehicle::logServiceEvent(const TourStop& tourStop, bool isStart) const {
    std::string startEndString = isStart ? "Start" : "End";
    std::string actionString = tourStop.getAction() == TourStopAction::PICKUP ? "pickup" : "dropoff";
    spdlog::info("{} {} for request {} at {} by vehicle {}", startEndString, actionString, tourStop.getRequestId(),
                 to_simple_string(engine.get().getTime()), vehicleData.getId());
}

bool Vehicle::hasFirstStopChanged(const std::vector<TourStop>& newTour) const {
    if (newTour.empty() || (!newTour.empty() && tour.empty())) {
        return true;
    }
    return newTour.at(0).getRequestId() != tour.at(0).getRequestId();
}

boost::posix_time::ptime Vehicle::getUpdateEventExecutionTime() const {
    boost::posix_time::ptime simulationTime = engine.get().getTime();
    boost::posix_time::ptime executionTime = engine.get().getTime();
    if (route) {
        executionTime = arc.value().getEndTime();
    } else if (serviceEndTime) {
        executionTime = serviceEndTime.value();
    }
    if (simulationTime > executionTime) {
        return simulationTime;
    }
    return executionTime;
}

void Vehicle::cancelPendingVehicleAction() {
    cancelEvent(pendingVehicleAction);
}

void Vehicle::cancelPendingRepositioningUpdate() {
    cancelEvent(pendingRepositioningUpdate);
}

void Vehicle::cancelPendingTourUpdate() {
    cancelEvent(pendingTourUpdate);
}

void Vehicle::cancelEvent(std::optional<const Event*>& event) {
    if (event) {
        engine.get().remove(*event.value());
        event.reset();
    }
}

bool Vehicle::hasTarget() const {
    return !tour.empty() || repositioningTarget;
}

bool Vehicle::isUpdatePending() const {
    return pendingRepositioningUpdate || pendingTourUpdate;
}

void Vehicle::storeStateIfChanged(const VehicleState& newState) {
    if (newState != state) {
        state = newState;
        this->simulationStats.get().changeVehicleState(vehicleData.getId(), state, this->engine.get().getTime());
    }
}

} // namespace drsim