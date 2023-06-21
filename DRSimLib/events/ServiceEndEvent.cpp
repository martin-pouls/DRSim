#include "ServiceEndEvent.h"
#include "include/drsim/Vehicle.h"
#include "core/Constants.h"

namespace drsim {
ServiceEndEvent::ServiceEndEvent(const boost::posix_time::ptime& creationTime,
                                 const boost::posix_time::ptime& executionTime, Vehicle& vehicle)
    : Event(Constants::SERVICE_END_EVENT_PRIORITY, creationTime, executionTime)
    , vehicle(vehicle) {
}

void ServiceEndEvent::execute() {
    vehicle.endService();
}
} // namespace drsim
