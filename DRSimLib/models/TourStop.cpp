#include "include/drsim/TourStop.h"

namespace drsim {
TourStop::TourStop(int requestId, TourStopAction action, const PointLatLon& location,
                   const boost::posix_time::ptime& earliestTime, const boost::posix_time::ptime& plannedDepartureTime,
                   const boost::posix_time::time_duration& serviceDuration, int passengerChange)
    : requestId(requestId)
    , action(action)
    , location(location)
    , earliestTime(earliestTime)
    , plannedDepartureTime(plannedDepartureTime)
    , serviceDuration(serviceDuration)
    , passengerChange(passengerChange) {
}

int TourStop::getRequestId() const {
    return requestId;
}

TourStopAction TourStop::getAction() const {
    return action;
}

const PointLatLon& TourStop::getLocation() const {
    return location;
}

const boost::posix_time::ptime& TourStop::getEarliestTime() const {
    return earliestTime;
}

const boost::posix_time::ptime& TourStop::getPlannedDepartureTime() const {
    return plannedDepartureTime;
}

const boost::posix_time::time_duration& TourStop::getServiceDuration() const {
    return serviceDuration;
}

int TourStop::getPassengerChange() const {
    return passengerChange;
}

} // namespace drsim