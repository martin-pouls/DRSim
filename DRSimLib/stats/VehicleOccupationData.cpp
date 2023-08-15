#include "VehicleOccupationData.h"
#include <algorithm>
#include <unordered_map>

namespace drsim {
VehicleOccupationData::VehicleOccupationData(std::vector<VehicleStateLogEntry>& stateLog,
                                             const std::unordered_map<unsigned, VehicleStats>& vehicleStatsById,
                                             const boost::posix_time::ptime& start, const boost::posix_time::ptime& end,
                                             const boost::posix_time::time_duration& step)
    : idleCounts()
    , activeCounts()
    , repositioningCounts()
    , timeStamps() {

    sortStateLogByTimestamp(stateLog);
    auto rollingTime = start;
    std::unordered_map<unsigned, VehicleState> rollingState = initializeRollingState(vehicleStatsById);
    while (rollingTime <= end) {
        updateCounts(rollingState);
        timeStamps.push_back(rollingTime);
        rollingTime += step;
        updateAndCutoffState(stateLog, rollingState, rollingTime);
    }
}

void VehicleOccupationData::updateCounts(const std::unordered_map<unsigned, VehicleState>& rollingState) {
    unsigned idleCount = 0, activeCount = 0, repositioningCount = 0;
    for (const auto& statePair : rollingState) {
        if (statePair.second == VehicleState::IDLE) {
            ++idleCount;
        } else if (statePair.second == VehicleState::ACTIVE) {
            ++activeCount;
        } else if (statePair.second == VehicleState::REPOSITIONING) {
            ++repositioningCount;
        }
    }
    idleCounts.push_back(idleCount);
    activeCounts.push_back(activeCount);
    repositioningCounts.push_back(repositioningCount);
}

void VehicleOccupationData::updateAndCutoffState(std::vector<VehicleStateLogEntry>& stateLog,
                                                 std::unordered_map<unsigned, VehicleState>& rollingState,
                                                 const boost::posix_time::ptime& rollingTime) {
    int cutOff = 0;
    for (int i = 0; i < stateLog.size(); ++i) {
        if (stateLog[i].getTimeStamp() < rollingTime) {
            rollingState[stateLog[i].getVehicleId()] = stateLog[i].getState();
        } else {
            cutOff = i;
            break;
        }
    }
    stateLog.erase(stateLog.begin(), stateLog.begin() + cutOff);
}

const std::vector<unsigned>& VehicleOccupationData::getIdleCounts() const {
    return idleCounts;
}

const std::vector<unsigned>& VehicleOccupationData::getActiveCounts() const {
    return activeCounts;
}

const std::vector<unsigned>& VehicleOccupationData::getRepositioningCounts() const {
    return repositioningCounts;
}

const std::vector<boost::posix_time::ptime>& VehicleOccupationData::getTimeStamps() const {
    return timeStamps;
}

void VehicleOccupationData::sortStateLogByTimestamp(std::vector<VehicleStateLogEntry>& stateLog) {
    std::sort(stateLog.begin(), stateLog.end(),
              [](const VehicleStateLogEntry& firstEntry, const VehicleStateLogEntry& secondEntry) {
                  return firstEntry.getTimeStamp() < secondEntry.getTimeStamp();
              });
}

std::unordered_map<unsigned, VehicleState> VehicleOccupationData::initializeRollingState(
    const std::unordered_map<unsigned, VehicleStats>& vehicleStatsById) const {
    std::unordered_map<unsigned, VehicleState> rollingState;
    for (auto& vehicleStatsPair : vehicleStatsById) {
        rollingState.insert_or_assign(vehicleStatsPair.first,
                                      vehicleStatsPair.second.getVehicleStateLog()[0].getState());
    }
    return rollingState;
}

} // namespace drsim