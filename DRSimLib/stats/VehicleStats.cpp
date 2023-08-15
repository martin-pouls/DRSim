#include "include/drsim/VehicleStats.h"

namespace drsim {
VehicleStats::VehicleStats(const VehicleData& vehicleData)
    : vehicleData(vehicleData) {
}

void VehicleStats::changeVehicleState(VehicleState state, const boost::posix_time::ptime& timeStamp) {
    vehicleStateLog.push_back(VehicleStateLogEntry(vehicleData.getId(), state, timeStamp));
}


void VehicleStats::addVehicleMovement(const VehicleMovementLogEntry& vehicleMovementLogEntry) {
    vehicleMovementLog.push_back(vehicleMovementLogEntry);
}

const std::vector<VehicleMovementLogEntry>& VehicleStats::getVehicleMovementLog() const {
    return vehicleMovementLog;
}

const std::vector<VehicleStateLogEntry>& VehicleStats::getVehicleStateLog() const {
    return vehicleStateLog;
}
}