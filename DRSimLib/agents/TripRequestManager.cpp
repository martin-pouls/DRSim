#include "include/drsim/TripRequestManager.h"
#include "include/drsim/PlanningServiceInterface.h"
#include "include/drsim/SimulationLog.h"
#include <spdlog/spdlog.h>

namespace drsim {
TripRequestManager::TripRequestManager(PlanningServiceInterface& planningServiceInterface, SimulationLog& simulationLog)
    : planningServiceInterface(planningServiceInterface)
    , simulationLog(simulationLog) {
}

void TripRequestManager::submitTripRequest(const TripRequestData& tripRequestData) {
    bool accepted = planningServiceInterface.submitTripRequest(tripRequestData);
    RequestState state = accepted ? RequestState::ACCEPTED : RequestState::REJECTED;
    simulationLog.logRequest(
        RequestLogEntry(tripRequestData.getId(), tripRequestData.getRequestTime(), state));
    spdlog::info("Submitted trip request {}", tripRequestData.getId());
}
} // namespace drsim