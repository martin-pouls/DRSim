#pragma once
#include "RoutingEngineInterface.h"
#include "PlanningServiceInterface.h"
#include "Scenario.h"
#include "TimeProvider.h"
#include <string>
#include "Engine.h"
#include "VehicleManager.h"
#include "TripRequestManager.h"
#include "SimulationLog.h"

namespace drsim {
class Simulation {
public:
    Simulation(const Scenario& scenario, PlanningServiceInterface& planningService, RoutingEngineInterface& routingEngine);

    void assignTour(const int vehicleId, const std::vector<TourStop>& tour);
    void assignRepositioning(const int vehicleId, const PointLatLon& target);
    void run();
    void registerTimeObserver(TimeObserver* observer);
    void writeSimulationLog(const std::string& outputFolder);

private:
    void initializeVehicleCreationEvents();
    void initializeRequestEvents();
    void initializeVehicleRemovalEvents();
    void initializeStartupFinishEvent();
    void initializeGpsEvent();
    
    Scenario scenario;
    PlanningServiceInterface& planningService;
    RoutingEngineInterface& routingEngine;
    Engine engine;
    SimulationLog simulationLog;
    VehicleManager vehicleManager;
    TripRequestManager tripRequestManager;
};
} // namespace drsim