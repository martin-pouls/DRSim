#pragma once
#include <vector>
#include "VehicleMovementLogEntry.h"
#include "VehicleStateLogEntry.h"
#include "RequestLogEntry.h"

namespace drsim {
class SimulationLog {
public:
    SimulationLog(const boost::posix_time::ptime& start, const boost::posix_time::ptime& end);

    void write(const std::string& folder);
    void logVehicleMovement(const VehicleMovementLogEntry& vehicleMovementLogEntry);
    void logVehicleState(const VehicleStateLogEntry& vehicleStateLogEntry);
    void logRequest(const RequestLogEntry& requestLogEntry);

private:
    boost::posix_time::ptime start;
    boost::posix_time::ptime end;
    std::vector<VehicleMovementLogEntry> vehicleMovementLog;
    std::vector<VehicleStateLogEntry> vehicleStateLog;
    std::vector<RequestLogEntry> requestLog;

    void writeSimulationLogJson(const std::string& folder);
    void writeVehicleMovementLog(const std::string& folder);
    void writeVehicleStateLog(const std::string& folder);
    void writeRequestLog(const std::string& folder);
};
} // namespace drsim