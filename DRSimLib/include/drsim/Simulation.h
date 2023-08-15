#pragma once
#include "Engine.h"
#include "PlanningServiceInterface.h"
#include "RoutingEngineInterface.h"
#include "Scenario.h"
#include "SimulationStats.h"
#include "TimeProvider.h"
#include "TripRequestManager.h"
#include "VehicleManager.h"
#include <string>

namespace drsim {

/**
 * @brief Main class to create a new simulation instance.
 **/
class Simulation {
public:
    /**
     * @param scenario The scenario to simulate.
     * @param planningService Reference to the planning service.
     * @param routingEngine Reference to the routing engine, which is used to obtain vehicle routes on the road network.
     **/
    Simulation(const Scenario& scenario, PlanningServiceInterface& planningService,
               RoutingEngineInterface& routingEngine);

    /**
     * @brief Assigns a tour to the chosen vehicle. The vehicle starts processing the tour immediately.
     *
     * @param vehicleId The ID of the selected vehicle.
     * @param tour The sequence of stops in the tour.
     **/
    void assignTour(const int vehicleId, const std::vector<TourStop>& tour);

    /**
     * @brief Assigns a repositioning target to the chosen vehicle. Only idle vehicles may be repositioned.
     *
     * @param vehicleId The ID of the selected vehicle.
     * @param target The location to which the vehicle will reposition.
     **/
    void assignRepositioning(const int vehicleId, const PointLatLon& target);

    /**
     * @brief Runs the simulation until the specified end in the scenario.
     **/
    void run();

    /**
     * @brief Registers a time observer. Time observers are notified whenever the time in the simulation changes.
     *
     * @param observer Pointer to the observer.
     **/
    void registerTimeObserver(TimeObserver* observer);

    /**
     * @brief Writes a set of output files in the specified folder. See the README for
     * more details on the written files.
     *
     * @param outputFolder The folder to which the files are written (must already exist).
     **/
    void writeSimulationStats(const std::string& outputFolder);

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
    SimulationStats simulationStats;
    VehicleManager vehicleManager;
    TripRequestManager tripRequestManager;
};
} // namespace drsim