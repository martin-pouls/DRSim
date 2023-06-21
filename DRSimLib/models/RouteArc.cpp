#include "include/drsim/RouteArc.h"

namespace drsim {

RouteArc::RouteArc(const boost::posix_time::time_duration& duration, unsigned distance,
                   const PointLatLon& startLocation, const PointLatLon& endLocation,
                   const boost::posix_time::ptime& startTime, const boost::posix_time::ptime& endTime)
    : duration(duration)
    , distance(distance)
    , startTime(startTime)
    , endTime(endTime)
    , startLocation(startLocation)
    , endLocation(endLocation) {
}

const boost::posix_time::time_duration& RouteArc::getDuration() const {
    return duration;
}

unsigned RouteArc::getDistance() const {
    return distance;
}

const PointLatLon& RouteArc::getStartLocation() const {
    return startLocation;
}

const PointLatLon& RouteArc::getEndLocation() const {
    return endLocation;
}

const boost::posix_time::ptime& RouteArc::getEndTime() const {
    return endTime;
}

const boost::posix_time::ptime& RouteArc::getStartTime() const {
    return startTime;
}

PointLatLon RouteArc::getLocationAtTime(const boost::posix_time::ptime& time) const {
    boost::posix_time::time_duration passedDuration = time - startTime;
    double progress = passedDuration.total_milliseconds() / duration.total_milliseconds();
    progress = std::min(progress, 1.0);
    double dLatitude = endLocation.getLatitude() - startLocation.getLatitude();
    double dLongitude = endLocation.getLongitude() - startLocation.getLongitude();
    return PointLatLon(startLocation.getLatitude() + progress * dLatitude,
                       startLocation.getLongitude() + progress * dLongitude);
}

} // namespace drsim