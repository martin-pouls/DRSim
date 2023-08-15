#include "include/drsim/SimulationStats.h"
#include "HistogramData.h"
#include "VehicleOccupationData.h"
#include <algorithm>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <fstream>
#include <iomanip>

namespace drsim {
SimulationStats::SimulationStats(const boost::posix_time::ptime& start, const boost::posix_time::ptime& end)
    : start(start)
    , end(end)
    , vehicleStatsById()
    , requestStatsById() {
}

void SimulationStats::write(const std::string& folder) {
    writeSimulationJson(folder);
    writeReplayData(folder);
    writeStatsData(folder);
}

void SimulationStats::addRequestStats(const TripRequestData& tripRequestData, bool accepted) {
    requestStatsById.insert_or_assign(tripRequestData.getId(), RequestStats(tripRequestData, accepted));
}

void SimulationStats::pickupRequest(unsigned requestId, const boost::posix_time::ptime& pickupTime) {
    requestStatsById.at(requestId).setPickupTime(pickupTime);
}

void SimulationStats::dropoffRequest(unsigned requestId, const boost::posix_time::ptime& dropoffTime) {
    requestStatsById.at(requestId).setDropoffTime(dropoffTime);
}

void SimulationStats::addVehicleStats(const VehicleData& vehicleData) {
    vehicleStatsById.insert_or_assign(vehicleData.getId(), VehicleStats(vehicleData));
}

void SimulationStats::changeVehicleState(unsigned vehicleId, VehicleState state,
                                         const boost::posix_time::ptime timeStamp) {
    vehicleStatsById.at(vehicleId).changeVehicleState(state, timeStamp);
}

void SimulationStats::addVehicleMovement(unsigned vehicleId, const VehicleMovementLogEntry& vehicleMovementLogEntry) {
    vehicleStatsById.at(vehicleId).addVehicleMovement(vehicleMovementLogEntry);
}

void SimulationStats::writeSimulationJson(const std::string& folder) {
    std::ofstream simulationFile(folder + "simulation.json");
    nlohmann::json json;
    json["start"] = to_iso_string(start);
    json["end"] = to_iso_string(end);
    simulationFile << json;
}

void SimulationStats::writeReplayData(const std::string& folder) {
    writeVehicleMovementReplay(folder);
    writeVehicleStateReplay(folder);
    writeRequestReplay(folder);
}

void SimulationStats::writeVehicleMovementReplay(const std::string& folder) {
    auto completeSortedMovementLog = getCompleteSortedMovementLog();
    std::ofstream vehicleMovementReplayFile(folder + "vehicleMovementReplay.csv");
    for (auto i = 0; i < completeSortedMovementLog.size(); ++i) {
        const auto& entry = completeSortedMovementLog.at(i);
        entry.writeReplayData(vehicleMovementReplayFile, start);
        if (i != completeSortedMovementLog.size() - 1) {
            vehicleMovementReplayFile << std::endl;
        }
    }
    vehicleMovementReplayFile.close();
}

void SimulationStats::writeVehicleStateReplay(const std::string& folder) {
    auto completeSortedStateLog = getCompleteSortedStateLog();
    std::ofstream vehicleStateReplayFile(folder + "vehicleStatesReplay.csv");
    for (auto i = 0; i < completeSortedStateLog.size(); ++i) {
        const auto& entry = completeSortedStateLog.at(i);
        entry.writeReplayData(vehicleStateReplayFile, start);
        if (i != completeSortedStateLog.size() - 1) {
            vehicleStateReplayFile << std::endl;
        }
    }
    vehicleStateReplayFile.close();
}

void SimulationStats::writeRequestReplay(const std::string& folder) {
    auto completeSortedRequestLog = getCompleteSortedRequestLog();
    std::ofstream requestStateReplayFile(folder + "requestReplay.csv");
    for (auto i = 0; i < completeSortedRequestLog.size(); ++i) {
        const auto& entry = completeSortedRequestLog.at(i);
        entry.write(requestStateReplayFile, start);
        if (i != completeSortedRequestLog.size() - 1) {
            requestStateReplayFile << std::endl;
        }
    }
    requestStateReplayFile.close();
}

void SimulationStats::writeStatsData(const std::string& folder) {
    std::ofstream simulationStatsFile(folder + "simulationStats.json");
    nlohmann::json json;
    writeRequestStatsData(json);
    writeVehicleStatsData(json);
    simulationStatsFile << json;
}

void SimulationStats::writeRequestStatsData(nlohmann::json& json) {
    nlohmann::json requestStatsJson;
    std::vector<int> waitingTimes, rideTimes, delays;
    unsigned numAccepted = 0, numRejected = 0;
    for (auto& requestStatsPair : requestStatsById) {
        requestStatsPair.second.isAccepted() ? ++numAccepted : ++numRejected;
        if (requestStatsPair.second.isPickedUp()) {
            waitingTimes.push_back(requestStatsPair.second.getWaitingTime().total_seconds());
        }
        if (requestStatsPair.second.isDroppedOff()) {
            rideTimes.push_back(requestStatsPair.second.getRideTime().total_seconds());
            delays.push_back(requestStatsPair.second.getDelay().total_seconds());
        }
    }
    writeHistogram(requestStatsJson, "waitingTime", waitingTimes, 60);
    writeHistogram(requestStatsJson, "rideTime", rideTimes, 180);
    writeHistogram(requestStatsJson, "delay", delays, 60);
    requestStatsJson["acceptedRequests"] = numAccepted;
    requestStatsJson["rejectedRequests"] = numRejected;
    json["requestStats"] = requestStatsJson;
}

void SimulationStats::writeVehicleStatsData(nlohmann::json& json) {
    auto stateLog = getCompleteSortedStateLog();
    VehicleOccupationData vehicleOccupationData(stateLog, vehicleStatsById, start, end, boost::posix_time::minutes(5));
    nlohmann::json vehicleStatsJson;
    vehicleStatsJson["idleCounts"] = vehicleOccupationData.getIdleCounts();
    vehicleStatsJson["activeCounts"] = vehicleOccupationData.getActiveCounts();
    vehicleStatsJson["repositioningCounts"] = vehicleOccupationData.getRepositioningCounts();
    const auto& timeStamps = vehicleOccupationData.getTimeStamps();
    std::vector<std::string> timeStampStrings;
    for (auto& timeStamp : timeStamps) {
        timeStampStrings.push_back(to_iso_string(timeStamp));
    }
    vehicleStatsJson["timeStamps"] = timeStampStrings;
    vehicleStatsJson["totalVehicles"] = vehicleStatsById.size();
    json["vehicleStats"] = vehicleStatsJson;
}

void SimulationStats::writeHistogram(nlohmann::json& json, const std::string& name, const std::vector<int>& values,
                                     unsigned step) {
    int max = *std::max_element(values.begin(), values.end());
    HistogramData data(values, 0, step);
    nlohmann::json histogramJson;
    histogramJson["buckets"] = data.getBoundaries();
    histogramJson["counts"] = data.getCounts();
    json[name] = histogramJson;
}

std::vector<VehicleMovementLogEntry> SimulationStats::getCompleteSortedMovementLog() {
    std::vector<VehicleMovementLogEntry> completeSortedMovementLog;
    for (auto& vehicleStatsPair : vehicleStatsById) {
        const auto& vehicleMovementLog = vehicleStatsPair.second.getVehicleMovementLog();
        completeSortedMovementLog.insert(completeSortedMovementLog.end(), vehicleMovementLog.begin(),
                                         vehicleMovementLog.end());
    }
    std::sort(completeSortedMovementLog.begin(), completeSortedMovementLog.end());
    return completeSortedMovementLog;
}

std::vector<VehicleStateLogEntry> SimulationStats::getCompleteSortedStateLog() {
    std::vector<VehicleStateLogEntry> completeSortedStateLog;
    for (auto& vehicleStatsPair : vehicleStatsById) {
        const auto& vehicleStateLog = vehicleStatsPair.second.getVehicleStateLog();
        completeSortedStateLog.insert(completeSortedStateLog.end(), vehicleStateLog.begin(), vehicleStateLog.end());
    }
    std::sort(completeSortedStateLog.begin(), completeSortedStateLog.end());
    return completeSortedStateLog;
}

std::vector<RequestLogEntry> SimulationStats::getCompleteSortedRequestLog() {
    std::vector<RequestLogEntry> completeSortedRequestLog;
    for (auto& requestStatsPair : requestStatsById) {
        const auto& requestLog = requestStatsPair.second.getRequestLog();
        completeSortedRequestLog.insert(completeSortedRequestLog.end(), requestLog.begin(), requestLog.end());
    }
    std::sort(completeSortedRequestLog.begin(), completeSortedRequestLog.end());
    return completeSortedRequestLog;
}
} // namespace drsim