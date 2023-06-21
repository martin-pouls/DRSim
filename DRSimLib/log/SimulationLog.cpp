#include "include/drsim/SimulationLog.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>

namespace drsim {
SimulationLog::SimulationLog(const boost::posix_time::ptime& start, const boost::posix_time::ptime& end)
    : start(start)
    , end(end)
    , vehicleMovementLog()
    , vehicleStateLog()
    , requestLog() {
}

void SimulationLog::write(const std::string& folder) {
    writeSimulationLogJson(folder);
    writeVehicleMovementLog(folder);
    writeVehicleStateLog(folder);
    writeRequestLog(folder);
}

void SimulationLog::logVehicleMovement(const VehicleMovementLogEntry& vehicleMovementLogEntry) {
    vehicleMovementLog.push_back(vehicleMovementLogEntry);
}

void SimulationLog::logVehicleState(const VehicleStateLogEntry& vehicleStateLogEntry) {
    vehicleStateLog.push_back(vehicleStateLogEntry);
}

void SimulationLog::logRequest(const RequestLogEntry& requestLogEntry) {
    requestLog.push_back(requestLogEntry);
}

void SimulationLog::writeSimulationLogJson(const std::string& folder) {
    std::ofstream simulationLogFile(folder + "simulationLog.json");
    nlohmann::json json;
    json["start"] = to_iso_string(start);
    json["end"] = to_iso_string(end);
    simulationLogFile << json;
}

void SimulationLog::writeVehicleMovementLog(const std::string& folder) {
    std::sort(vehicleMovementLog.begin(), vehicleMovementLog.end());
    std::ofstream vehicleMovementLogFile(folder + "movementLog.csv");
    for (auto i = 0; i < vehicleMovementLog.size(); ++i) {
        const auto& entry = vehicleMovementLog.at(i);
        entry.write(vehicleMovementLogFile, start);
        if (i != vehicleMovementLog.size() - 1) vehicleMovementLogFile << std::endl;
    }
    vehicleMovementLogFile.close();
}

void SimulationLog::writeVehicleStateLog(const std::string& folder){
    std::sort(vehicleStateLog.begin(), vehicleStateLog.end());
    std::ofstream vehicleStateLogFile(folder + "vehicleStatesLog.csv");
    for (auto i = 0; i < vehicleStateLog.size(); ++i) {
        const auto& entry = vehicleStateLog.at(i);
        entry.write(vehicleStateLogFile, start);
        if (i != vehicleStateLog.size() - 1) vehicleStateLogFile << std::endl;
    }
    vehicleStateLogFile.close();
}

void SimulationLog::writeRequestLog(const std::string& folder){
    std::sort(requestLog.begin(), requestLog.end());
    std::ofstream requestStateLogFile(folder + "requestLog.csv");
    for (auto i = 0; i < requestLog.size(); ++i) {
        const auto& entry = requestLog.at(i);
        entry.write(requestStateLogFile, start);
        if (i != requestLog.size() - 1) requestStateLogFile << std::endl;
    }
    requestStateLogFile.close();
}
} // namespace drsim