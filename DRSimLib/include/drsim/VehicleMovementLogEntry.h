#pragma once
#include <boost/date_time/posix_time/ptime.hpp>
#include "PointLatLon.h"

namespace drsim {
class VehicleMovementLogEntry {
public:
    VehicleMovementLogEntry(int vehicleId, const boost::posix_time::ptime& startTimeStamp,
                            const boost::posix_time::ptime& endTimeStamp, const PointLatLon& startLocation,
                            const PointLatLon& endLocation);

    void writeReplayData(std::ostream& stream, const boost::posix_time::ptime& simulationStart) const;
    bool operator<(const VehicleMovementLogEntry& other) const;

private:
    int vehicleId;
    boost::posix_time::ptime startTimeStamp;
    boost::posix_time::ptime endTimeStamp;
    PointLatLon startLocation;
    PointLatLon endLocation;
};
} // namespace drsim