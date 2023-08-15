#include "include/drsim/VehicleStateLogEntry.h"

namespace drsim {

unsigned VehicleStateLogEntry::stateLogCounter = 0;

VehicleStateLogEntry::VehicleStateLogEntry(int vehicleId, const VehicleState& state,
                                           const boost::posix_time::ptime& timeStamp)
    : vehicleId(vehicleId)
    , state(state)
    , timeStamp(timeStamp)
    , counter(stateLogCounter++) {
}

std::string toString(const VehicleState& state) {
    if (state == VehicleState::ACTIVE) {
        return "A";
    } else if (state == VehicleState::IDLE) {
        return "I";
    } else if (state == VehicleState::REPOSITIONING) {
        return "R";
    }
    throw std::exception("Invalid vehicle state");
}

void VehicleStateLogEntry::writeReplayData(std::ostream& stream,
                                           const boost::posix_time::ptime& simulationStart) const {
    boost::posix_time::time_duration difference = timeStamp - simulationStart;
    stream << vehicleId << ";" << difference.total_seconds() << ";" << toString(state);
}

bool VehicleStateLogEntry::operator<(const VehicleStateLogEntry& other) const {
    if (this->vehicleId == other.vehicleId) {
        if (this->timeStamp != other.timeStamp) {
            return this->timeStamp < other.timeStamp;
        } else {
            return this->counter < other.counter;
        }
    }
    return this->vehicleId < other.vehicleId;
}

const VehicleState& VehicleStateLogEntry::getState() const {
    return state;
}

const boost::posix_time::ptime& VehicleStateLogEntry::getTimeStamp() const {
    return timeStamp;
}

int VehicleStateLogEntry::getVehicleId() const {
    return vehicleId;
}
} // namespace drsim