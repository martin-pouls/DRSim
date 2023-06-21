#include "TourStopArrivalEvent.h"
#include "include/drsim/Vehicle.h"
#include "core/Constants.h"

namespace drsim {
TourStopArrivalEvent::TourStopArrivalEvent(const boost::posix_time::ptime& creationTime,
                                           const boost::posix_time::ptime& executionTime, Vehicle& vehicle)
    : Event(Constants::TOUR_STOP_ARRIVAL_EVENT_PRIORITY, creationTime, executionTime)
    , vehicle(vehicle) {
}

void TourStopArrivalEvent::execute() {
    vehicle.arriveAtTourStop();
}
} // namespace drsim
