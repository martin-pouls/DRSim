#pragma once
#include "Route.h"
#include "TourStop.h"
#include "VehicleData.h"
#include <optional>
#include <vector>
#include "VehicleState.h"

namespace drsim {
class RoutingEngineInterface;
class PlanningServiceInterface;
class Engine;
class Event;
class SimulationLog;

class Vehicle {
public:
    Vehicle(const VehicleData& vehicleData, PlanningServiceInterface& planningService,
            RoutingEngineInterface& routingEngine, Engine& engine, SimulationLog& simulationLog);

    PointLatLon getLocation() const;
    int getId() const;
    void assignTour(const std::vector<TourStop>& tour);
    void assignRepositioning(const PointLatLon& target);
    void updateTour(const std::vector<TourStop>& tour);
    void updateRepositioning(const PointLatLon& target);
    void endArc(const RouteArc& arc);
    void arriveAtTourStop();
    void startService();
    void endService();
    void arriveAtRepositioning();

private:
    VehicleData vehicleData;
    std::reference_wrapper<PlanningServiceInterface> planningService;
    std::reference_wrapper<RoutingEngineInterface> routingEngine;
    std::reference_wrapper<Engine> engine;
    std::reference_wrapper<SimulationLog> simulationLog;
    VehicleState state;
    PointLatLon currentLocation;
    std::vector<TourStop> tour;
    std::optional<Route> route;
    std::optional<RouteArc> arc;
    std::optional<boost::posix_time::ptime> serviceEndTime;
    std::optional<PointLatLon> repositioningTarget;
    std::optional<const Event*> pendingTourUpdate;
    std::optional<const Event*> pendingRepositioningUpdate;
    std::optional<const Event*> pendingVehicleAction;

    bool hasFirstStopChanged(const std::vector<TourStop>& newTour) const;
    boost::posix_time::ptime getUpdateEventExecutionTime() const;
    void cancelEvent(std::optional<const Event*>& event);
    void cancelPendingVehicleAction();
    void cancelPendingRepositioningUpdate();
    void cancelPendingTourUpdate();
    void moveToNextTarget();
    bool hasTarget() const;
    void scheduleArrivalEvent();
    void moveToNextArc();
    bool isUpdatePending() const;
    void logServiceEvent(const TourStop& tourStop, bool isStart) const;
    void storeStateIfChanged(const VehicleState& newState);
};
} // namespace drsim