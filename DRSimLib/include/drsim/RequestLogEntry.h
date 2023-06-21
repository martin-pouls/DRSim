#pragma once
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {

enum class RequestState { ACCEPTED, REJECTED, PICKED_UP, DROPPED_OFF };

class RequestLogEntry {
public:
    RequestLogEntry(unsigned requestId, const boost::posix_time::ptime& timeStamp, const RequestState& state);
    void write(std::ostream& stream, const boost::posix_time::ptime& simulationStart) const;
    bool operator<(const RequestLogEntry& other) const;
private:
    unsigned requestId;
    boost::posix_time::ptime timeStamp;
    RequestState state;
    unsigned counter;

    static unsigned requestLogCounter;
};
} // namespace drsim