#include "ServiceStartEvent.h"
#include "include/drsim/Vehicle.h"
#include "core/Constants.h"

namespace drsim {
ServiceStartEvent::ServiceStartEvent(const boost::posix_time::ptime& creationTime,
                                     const boost::posix_time::ptime& executionTime, Vehicle& vehicle)
    : Event(Constants::SERVICE_START_EVENT_PRIORITY, creationTime, executionTime)
    , vehicle(vehicle) {
}

void ServiceStartEvent::execute() {
    vehicle.startService();
}
} // namespace drsim
