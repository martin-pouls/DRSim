#pragma once
#include "VehicleState.h"
#include <boost/date_time/posix_time/ptime.hpp>
#include <ostream>

namespace drsim {

class VehicleStateLogEntry {
public:
    VehicleStateLogEntry(int vehicleId, const VehicleState& state, const boost::posix_time::ptime& timeStamp);

    void writeReplayData(std::ostream& stream, const boost::posix_time::ptime& simulationStart) const;
    bool operator<(const VehicleStateLogEntry& other) const;
    void setCounter(unsigned counter);
    const VehicleState& getState() const;
    const boost::posix_time::ptime& getTimeStamp() const;
    int getVehicleId() const;

private:
    int vehicleId;
    VehicleState state;
    boost::posix_time::ptime timeStamp;
    unsigned counter;

    static unsigned stateLogCounter;
};
} // namespace drsim