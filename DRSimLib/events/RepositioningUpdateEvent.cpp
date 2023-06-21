#include "RepositioningUpdateEvent.h"
#include "include/drsim/Vehicle.h"
#include "core/Constants.h"

namespace drsim {
RepositioningUpdateEvent::RepositioningUpdateEvent(const boost::posix_time::ptime& creationTime,
                                                   const boost::posix_time::ptime& executionTime, Vehicle& vehicle,
                                                   const PointLatLon& target)
    : Event(Constants::RELOCATION_UPDATE_EVENT_PRIORITY, creationTime, executionTime)
    , vehicle(vehicle)
    , target(target) {
}

void RepositioningUpdateEvent::execute() {
    vehicle.updateRepositioning(target);
}
} // namespace drsim
