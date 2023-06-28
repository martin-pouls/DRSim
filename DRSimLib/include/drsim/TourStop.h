#pragma once
#include "PointLatLon.h"
#include "boost/date_time/posix_time/ptime.hpp"

namespace drsim {

enum class TourStopAction { PICKUP, DROPOFF };

/**
 * @brief A stop in the tour of a vehicle.
 **/
class TourStop {
public:
    /**
     * @param requestId The ID of the requests for which the action is performed.
     * @param action The action (pickup or dropoff) at this stop.
     * @param location The location of the stop.
     * @param earliestTime The earliest time at which the action may be performed.
     * @param plannedDepartureTime The planned time of departure at the stop.
     * @param serviceDuration The service duration for the action at this stop.
     * @param passengerChange The change in passengers that are boarding or alighting.
     **/
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