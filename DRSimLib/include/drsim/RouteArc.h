#pragma once
#include "PointLatLon.h"
#include "boost/date_time/posix_time/ptime.hpp"

namespace drsim {

class RouteArc {
public:
    RouteArc(const boost::posix_time::time_duration& duration, unsigned distance, const PointLatLon& startLocation,
             const PointLatLon& endLocation, const boost::posix_time::ptime& startTime,
             const boost::posix_time::ptime& endTime);

    const boost::posix_time::time_duration& getDuration() const;
    unsigned getDistance() const;
    const boost::posix_time::ptime& getStartTime() const;
    const boost::posix_time::ptime& getEndTime() const;
    const PointLatLon& getStartLocation() const;
    const PointLatLon& getEndLocation() const;
    PointLatLon getLocationAtTime(const boost::posix_time::ptime& time) const;

private:
    boost::posix_time::time_duration duration;
    unsigned distance;
    PointLatLon startLocation;
    PointLatLon endLocation;
    boost::posix_time::ptime startTime;
    boost::posix_time::ptime endTime;
};
} // namespace drsim