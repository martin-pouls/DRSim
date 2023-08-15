#include "include/drsim/TripRequestManager.h"
#include "include/drsim/PlanningServiceInterface.h"
#include "include/drsim/SimulationStats.h"
#include <spdlog/spdlog.h>

namespace drsim {
TripRequestManager::TripRequestManager(PlanningServiceInterface& planningServiceInterface, SimulationStats& simulationStats)
    : planningServiceInterface(planningServiceInterface)
    , simulationStats(simulationStats) {
}

void TripRequestManager::submitTripRequest(const TripRequestData& tripRequestData) {
    bool accepted = planningServiceInterface.submitTripRequest(tripRequestData);
    simulationStats.addRequestStats(tripRequestData, accepted);
    spdlog::info("Submitted trip request {}", tripRequestData.getId());
}
} // namespace drsim