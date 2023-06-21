#include "ArcEndEvent.h"
#include "include/drsim/Vehicle.h"

namespace drsim {

ArcEndEvent::ArcEndEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                         Vehicle& vehicle, RouteArc& arc)
    : Event(Constants::ARC_END_EVENT_PRIORITY, creationTime, executionTime)
    , vehicle(vehicle)
    , arc(arc) {
}

void ArcEndEvent::execute() {
    vehicle.endArc(arc);
}

} // namespace drsim