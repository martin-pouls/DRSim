#pragma once
#include "PointLatLon.h"
#include "boost/date_time/posix_time/ptime.hpp"

namespace drsim {

enum class TourStopAction { PICKUP, DROPOFF };

class TourStop {
public:
    TourStop(int requestId, TourStopAction action, const PointLatLon& location,
             const boost::posix_time::ptime& earliestTime, const boost::posix_time::ptime& plannedDepartureTime,
             const boost::posix_time::time_duration& serviceDuration, int passengerChange);

    int getRequestId() const;
    TourStopAction getAction() const;
    const PointLatLon& getLocation() const;
    const boost::posix_time::ptime& getEarliestTime() const;
    const boost::posix_time::ptime& getPlannedDepartureTime() const;
    const boost::posix_time::time_duration& getServiceDuration() const;
    int getPassengerChange() const;

private:
    int requestId;
    TourStopAction action;
    PointLatLon location;
    boost::posix_time::ptime earliestTime;
    boost::posix_time::ptime plannedDepartureTime;
    boost::posix_time::time_duration serviceDuration;
    int passengerChange;
};
} // namespace drsim