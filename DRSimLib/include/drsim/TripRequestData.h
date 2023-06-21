#pragma once
#include "PointLatLon.h"
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {
class TripRequestData {
public:
    TripRequestData(int id, const PointLatLon& pickupLocation, const PointLatLon& dropoffLocation,
                    const boost::posix_time::ptime& requestTime, const boost::posix_time::ptime& earliestPickupTime,
                    const boost::posix_time::ptime& latestPickupTime,
                    const boost::posix_time::time_duration& maximumTraveltime,
                    const boost::posix_time::time_duration& directTraveltime, unsigned passengerCount,
                    const boost::posix_time::time_duration& serviceDuration, bool sharingAllowed);

    int getId() const;
    const PointLatLon& getPickupLocation() const;
    const PointLatLon& getDropoffLocation() const;
    const boost::posix_time::ptime& getRequestTime() const;
    const boost::posix_time::ptime& getEarliestPickupTime() const;
    const boost::posix_time::ptime& getLatestPickupTime() const;
    const boost::posix_time::time_duration& getMaximumTraveltime() const;
    const boost::posix_time::time_duration& getDirectTraveltime() const;
    unsigned getPassengerCount() const;
    const boost::posix_time::time_duration& getServiceDuration() const;
    bool isSharingAllowed() const;

private:
    int id;
    PointLatLon pickupLocation;
    PointLatLon dropoffLocation;
    boost::posix_time::ptime requestTime;
    boost::posix_time::ptime earliestPickupTime;
    boost::posix_time::ptime latestPickupTime;
    boost::posix_time::time_duration maximumTraveltime;
    boost::posix_time::time_duration directTraveltime;
    unsigned passengerCount;
    boost::posix_time::time_duration serviceDuration;
    bool sharingAllowed;
};
} // namespace drsim