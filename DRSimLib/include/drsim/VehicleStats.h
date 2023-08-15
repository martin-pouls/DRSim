#pragma once
#include "VehicleData.h"
#include "VehicleStateLogEntry.h"
#include "VehicleMovementLogEntry.h"
#include <vector>

namespace drsim {
class VehicleStats {
public:
    VehicleStats(const VehicleData& vehicleData);
    void changeVehicleState(VehicleState state, const boost::posix_time::ptime& timeStamp);
    void addVehicleMovement(const VehicleMovementLogEntry& vehicleMovementLogEntry);
    const std::vector<VehicleMovementLogEntry>& getVehicleMovementLog() const;
    const std::vector<VehicleStateLogEntry>& getVehicleStateLog() const;

private:
    VehicleData vehicleData;
    std::vector<VehicleStateLogEntry> vehicleStateLog;
    std::vector<VehicleMovementLogEntry> vehicleMovementLog;
};
}