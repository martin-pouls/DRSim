#include "include/drsim/Simulation.h"
#include "events/GpsEvent.h"
#include "events/StartupFinishEvent.h"
#include "events/TripRequestEvent.h"
#include "events/VehicleCreationEvent.h"
#include "events/VehicleRemovalEvent.h"
#include <memory>

namespace drsim {
Simulation::Simulation(const Scenario& scenario, PlanningServiceInterface& planningService,
                       RoutingEngineInterface& routingEngine)
    : scenario(scenario)
    , planningService(planningService)
    , routingEngine(routingEngine)
    , engine(scenario.getStart())
    , simulationStats(scenario.getStart(), scenario.getEnd())
    , vehicleManager(planningService, routingEngine, engine, simulationStats)
    , tripRequestManager(planningService, simulationStats) {
    initializeVehicleCreationEvents();
    initializeRequestEvents();
    initializeVehicleRemovalEvents();
    initializeStartupFinishEvent();
    initializeGpsEvent();
}

void Simulation::assignTour(const int vehicleId, const std::vector<TourStop>& tour) {
    auto& vehicle = vehicleManager.getVehicleById(vehicleId);
    vehicle.assignTour(tour);
}

void Simulation::assignRepositioning(const int vehicleId, const PointLatLon& target) {
    auto& vehicle = vehicleManager.getVehicleById(vehicleId);
    vehicle.assignRepositioning(target);
}

void Simulation::run() {
    engine.runUntil(scenario.getEnd());
}

void Simulation::registerTimeObserver(TimeObserver* observer) {
    engine.registerTimeObserver(observer);
}

void Simulation::writeSimulationStats(const std::string& outputFolder) {
    simulationStats.write(outputFolder);
}

void Simulation::initializeVehicleCreationEvents() {
    for (const auto& vehicle : scenario.getVehicles()) {
        std::unique_ptr<Event> event =
            std::make_unique<VehicleCreationEvent>(scenario.getStart(), scenario.getStart(), vehicle, vehicleManager);
        engine.add(event);
    }
}

void Simulation::initializeRequestEvents() {
    for (const auto& request : scenario.getTripRequests()) {
        std::unique_ptr<Event> event = std::make_unique<TripRequestEvent>(scenario.getStart(), request.getRequestTime(),
                                                                          request, tripRequestManager);
        engine.add(event);
    }
}
void Simulation::initializeVehicleRemovalEvents() {
    for (const auto& vehicle : scenario.getVehicles()) {
        std::unique_ptr<Event> event = std::make_unique<VehicleRemovalEvent>(scenario.getStart(), scenario.getEnd(),
                                                                             vehicleManager, vehicle.getId());
        engine.add(event);
    }
}
void Simulation::initializeStartupFinishEvent() {
    std::unique_ptr<Event> event = std::make_unique<StartupFinishEvent>(
        scenario.getStart(), scenario.getStart() + scenario.getStartupDuration(), planningService);
    engine.add(event);
}

void Simulation::initializeGpsEvent() {
    std::unique_ptr<Event> event = std::make_unique<GpsEvent>(scenario.getStart(), scenario.getStart(), vehicleManager);
    engine.add(event);
}

} // namespace drsim