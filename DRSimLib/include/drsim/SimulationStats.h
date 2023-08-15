#pragma once
#include "RequestLogEntry.h"
#include "RequestStats.h"
#include "TripRequestData.h"
#include "VehicleData.h"
#include "VehicleMovementLogEntry.h"
#include "VehicleStats.h"
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

namespace drsim {
class SimulationStats {
public:
    SimulationStats(const boost::posix_time::ptime& start, const boost::posix_time::ptime& end);

    void write(const std::string& folder);

    void addRequestStats(const TripRequestData& tripRequestData, bool accepted);
    void pickupRequest(unsigned requestId, const boost::posix_time::ptime& pickupTime);
    void dropoffRequest(unsigned requestId, const boost::posix_time::ptime& dropoffTime);

    void addVehicleStats(const VehicleData& vehicleData);
    void changeVehicleState(unsigned vehicleId, VehicleState state, const boost::posix_time::ptime timeStamp);
    void addVehicleMovement(unsigned vehicleId, const VehicleMovementLogEntry& vehicleMovementLogEntry);

private:
    boost::posix_time::ptime start;
    boost::posix_time::ptime end;
    std::unordered_map<unsigned, VehicleStats> vehicleStatsById;
    std::unordered_map<unsigned, RequestStats> requestStatsById;

    void writeSimulationJson(const std::string& folder);

    void writeReplayData(const std::string& folder);
    void writeVehicleMovementReplay(const std::string& folder);
    void writeVehicleStateReplay(const std::string& folder);
    void writeRequestReplay(const std::string& folder);

    void writeStatsData(const std::string& folder);
    void writeRequestStatsData(nlohmann::json& json);
    void writeVehicleStatsData(nlohmann::json& json);
    void writeHistogram(nlohmann::json& json, const std::string& name, const std::vector<int>& values, unsigned step);

    std::vector<VehicleMovementLogEntry> getCompleteSortedMovementLog();
    std::vector<VehicleStateLogEntry> getCompleteSortedStateLog();
    std::vector<RequestLogEntry> getCompleteSortedRequestLog();
};
} // namespace drsim