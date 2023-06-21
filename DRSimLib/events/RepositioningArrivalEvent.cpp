#include "RepositioningArrivalEvent.h"
#include "core/Constants.h"
#include "include/drsim/Vehicle.h"

namespace drsim {
RepositioningArrivalEvent::RepositioningArrivalEvent(const boost::posix_time::ptime& creationTime,
                                                     const boost::posix_time::ptime& executionTime, Vehicle& vehicle)
    : Event(Constants::REPOSITIONING_ARRIVAL_EVENT_PRIORITY, creationTime, executionTime)
    , vehicle(vehicle) {
}

void RepositioningArrivalEvent::execute() {
    vehicle.arriveAtRepositioning();
}
} // namespace drsim
