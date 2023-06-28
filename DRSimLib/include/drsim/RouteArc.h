#pragma once
#include "PointLatLon.h"
#include "boost/date_time/posix_time/ptime.hpp"

namespace drsim {

/**
 * @brief A single arc in a route.
 **/
class RouteArc {
public:
    /**
     * @param duration The duration of this arc.
     * @param distance The distance of this arc (in meters).
     * @param startLocation The start location.
     * @param endLocation The end location
     * @param startTime The departure time at the start location.
     * @param endTime The arrival time at the end location.
     **/
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