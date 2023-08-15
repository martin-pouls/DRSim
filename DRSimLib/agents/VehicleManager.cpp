#include "include/drsim/VehicleManager.h"
#include "include/drsim/Engine.h"
#include "include/drsim/PlanningServiceInterface.h"
#include "include/drsim/RoutingEngineInterface.h"
#include "events/GpsEvent.h"
#include <spdlog/spdlog.h>

namespace drsim {
VehicleManager::VehicleManager(PlanningServiceInterface& planningService, RoutingEngineInterface& routingEngine,
                               Engine& engine, SimulationStats& simulationStats)
    : planningService(planningService)
    , routingEngine(routingEngine)
    , engine(engine)
    , simulationStats(simulationStats) {
}

void VehicleManager::createVehicle(const VehicleData& vehicleData) {
    vehicles.push_back(Vehicle(vehicleData, planningService, routingEngine, engine, simulationStats));
    vehicleIndexById.insert(std::make_pair(vehicleData.getId(), vehicles.size() - 1));
    spdlog::info("Created vehicle {}", vehicleData.getId());
}

void VehicleManager::removeVehicle(int vehicleId) {
    auto index = vehicleIndexById.at(vehicleId);
    vehicles.erase(vehicles.begin() + index);
    vehicleIndexById.erase(vehicleId);
    for (auto& indexPair : vehicleIndexById) {
        if (indexPair.second > index) {
            indexPair.second--;
        }
    }
    planningService.removeVehicle(engine.getTime(), vehicleId);
    spdlog::info("Removed vehicle {}", vehicleId);
}

void VehicleManager::sendGpsMessages() {
    spdlog::debug("Sending GPS messages");
    for (const auto& vehicle : vehicles) {
        planningService.updateVehicleLocation(engine.getTime(), vehicle.getLocation(), vehicle.getId());
    }
	std::unique_ptr<Event> event = std::make_unique<GpsEvent>(engine.getTime(), engine.getTime() + boost::posix_time::seconds(1), *this);
	engine.add(event);
}

Vehicle& VehicleManager::getVehicleById(int vehicleId) {
    auto index = vehicleIndexById.at(vehicleId);
    return vehicles.at(index);
}

} // namespace drsim