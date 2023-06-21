#pragma once
#include "Vehicle.h"
#include <unordered_map>

namespace drsim {
class PlanningServiceInterface;
class RoutingEngineInterface;
class Engine;
class SimulationLog;

class VehicleManager {
public:
    VehicleManager(PlanningServiceInterface& planningService, RoutingEngineInterface& routingEngine, Engine& engine,
                   SimulationLog& simulationLog);

    void createVehicle(const VehicleData& vehicleData);
    void removeVehicle(int vehicleId);
    void sendGpsMessages();
    Vehicle& getVehicleById(int vehicleId);

private:
    PlanningServiceInterface& planningService;
    RoutingEngineInterface& routingEngine;
    Engine& engine;
    SimulationLog& simulationLog;

    std::vector<Vehicle> vehicles;
    std::unordered_map<int, size_t> vehicleIndexById;
};
} // namespace drsim