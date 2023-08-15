#include "include/drsim/VehicleMovementLogEntry.h"

namespace drsim {
VehicleMovementLogEntry::VehicleMovementLogEntry(int vehicleId, const boost::posix_time::ptime& startTimeStamp,
                                                 const boost::posix_time::ptime& endTimeStamp,
                                                 const PointLatLon& startLocation, const PointLatLon& endLocation)
    : vehicleId(vehicleId)
    , startTimeStamp(startTimeStamp)
    , endTimeStamp(endTimeStamp)
    , startLocation(startLocation)
    , endLocation(endLocation) {
}

void VehicleMovementLogEntry::writeReplayData(std::ostream& stream, const boost::posix_time::ptime& simulationStart) const {
    boost::posix_time::time_duration startDifference = startTimeStamp - simulationStart;
    boost::posix_time::time_duration endDifference = endTimeStamp - simulationStart;
    stream << vehicleId << ";" << startDifference.total_seconds() << ";" << endDifference.total_seconds() << ";";
    stream << startLocation.getLatitude() << ";" << startLocation.getLongitude() << ";";
    stream << endLocation.getLatitude() << ";" << endLocation.getLongitude();
}

bool VehicleMovementLogEntry::operator<(const VehicleMovementLogEntry& other) const {
    if (this->vehicleId == other.vehicleId) {
        if (this->startTimeStamp != other.startTimeStamp) {
            return this->startTimeStamp < other.startTimeStamp;
        } else {
            return this->endTimeStamp < other.endTimeStamp;
        }
    }
    return this->vehicleId < other.vehicleId;
}
} // namespace drsim