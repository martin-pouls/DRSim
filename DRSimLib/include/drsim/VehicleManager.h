#pragma once
#include "Vehicle.h"
#include <unordered_map>

namespace drsim {
class PlanningServiceInterface;
class RoutingEngineInterface;
class Engine;
class SimulationStats;

class VehicleManager {
public:
    VehicleManager(PlanningServiceInterface& planningService, RoutingEngineInterface& routingEngine, Engine& engine,
                   SimulationStats& simulationStats);

    void createVehicle(const VehicleData& vehicleData);
    void removeVehicle(int vehicleId);
    void sendGpsMessages();
    Vehicle& getVehicleById(int vehicleId);

private:
    PlanningServiceInterface& planningService;
    RoutingEngineInterface& routingEngine;
    Engine& engine;
    SimulationStats& simulationStats;

    std::vector<Vehicle> vehicles;
    std::unordered_map<int, size_t> vehicleIndexById;
};
} // namespace drsim