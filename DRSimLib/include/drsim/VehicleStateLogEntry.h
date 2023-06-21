#include <boost/date_time/posix_time/ptime.hpp>
#include <ostream>
#include "VehicleState.h"

namespace drsim {

class VehicleStateLogEntry {
public:
    VehicleStateLogEntry(int vehicleId, const VehicleState& state, const boost::posix_time::ptime& timeStamp);

    void write(std::ostream& stream, const boost::posix_time::ptime& simulationStart) const;
    bool operator<(const VehicleStateLogEntry& other) const;
    void setCounter(unsigned counter);

private:
    int vehicleId;
    VehicleState state;
    boost::posix_time::ptime timeStamp;
    unsigned counter;

    static unsigned stateLogCounter;
};
} // namespace drsim