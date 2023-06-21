#include "TourUpdateEvent.h"
#include "include/drsim/Vehicle.h"
#include "core/Constants.h"

namespace drsim {
TourUpdateEvent::TourUpdateEvent(const boost::posix_time::ptime& creationTime,
                                 const boost::posix_time::ptime& executionTime, Vehicle& vehicle,
                                 const std::vector<TourStop>& tour)
    : Event(Constants::TOUR_UPDATE_EVENT_PRIORITY, creationTime, executionTime)
    , vehicle(vehicle)
    , tour(tour) {
}

void TourUpdateEvent::execute() {
    vehicle.updateTour(tour);
}
} // namespace drsim
