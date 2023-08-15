#pragma once
#include "include/drsim/VehicleStateLogEntry.h"
#include "include/drsim/VehicleStats.h"
#include <unordered_map>
#include <vector>

namespace drsim {
class VehicleOccupationData {
public:
    VehicleOccupationData(std::vector<VehicleStateLogEntry>& stateLog,
                          const std::unordered_map<unsigned, VehicleStats>& vehicleStatsById,
                          const boost::posix_time::ptime& start, const boost::posix_time::ptime& end,
                          const boost::posix_time::time_duration& step);

    const std::vector<unsigned>& getIdleCounts() const;
    const std::vector<unsigned>& getActiveCounts() const;
    const std::vector<unsigned>& getRepositioningCounts() const;
    const std::vector<boost::posix_time::ptime>& getTimeStamps() const;

private:
    std::vector<unsigned> idleCounts;
    std::vector<unsigned> activeCounts;
    std::vector<unsigned> repositioningCounts;
    std::vector<boost::posix_time::ptime> timeStamps;

    void sortStateLogByTimestamp(std::vector<VehicleStateLogEntry>& stateLog);
    std::unordered_map<unsigned, VehicleState>
    initializeRollingState(const std::unordered_map<unsigned, VehicleStats>& vehicleStatsById) const;
    void updateCounts(const std::unordered_map<unsigned, VehicleState>& rollingState);
    void updateAndCutoffState(std::vector<VehicleStateLogEntry>& stateLog,
                              std::unordered_map<unsigned, VehicleState>& rollingState,
                              const boost::posix_time::ptime& rollingTime);
};
} // namespace drsim