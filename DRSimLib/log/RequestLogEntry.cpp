#include "include/drsim/RequestLogEntry.h"

namespace drsim {
unsigned RequestLogEntry::requestLogCounter = 0;

RequestLogEntry::RequestLogEntry(unsigned requestId, const boost::posix_time::ptime& timeStamp,
                                 const RequestState& state)
    : requestId(requestId)
    , timeStamp(timeStamp)
    , state(state)
    , counter(requestLogCounter++) {
}

std::string toString(const RequestState& state) {
    if (state == RequestState::ACCEPTED) {
        return "A";
    } else if (state == RequestState::REJECTED) {
        return "R";
    } else if (state == RequestState::PICKED_UP) {
        return "P";
    } else if (state == RequestState::DROPPED_OFF) {
        return "D";
    }
    throw std::exception("Invalid request state");
}

void RequestLogEntry::write(std::ostream& stream, const boost::posix_time::ptime& simulationStart) const {
    stream << requestId << ";" << (timeStamp - simulationStart).total_seconds() << ";" << toString(state);
}

bool RequestLogEntry::operator<(const RequestLogEntry& other) const {
    if (timeStamp != other.timeStamp) {
        return timeStamp < other.timeStamp;
    } else {
        return counter < other.counter;
    }
}
} // namespace drsim