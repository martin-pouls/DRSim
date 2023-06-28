#pragma once
#include "PointLatLon.h"
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {
/**
 * @brief Data concerning a trip request that is submitted during the simulation.
 **/
class TripRequestData {
public:
    /**
     * @param id The unique identifier of the trip request.
     * @param pickupLocation The desired pickup location of the passengers.
     * @param dropoffLocation The desired dropoff location of the passengers.
     * @param requestTime The time at which the trip request is sumitted.
     * @param earliestPickupTime The earliest possible pickup time. Must be >= requestTime.
     * @param latestPickupTime The latest possible pickup time. Must be >= earliestPickupTime.
     * @param maximumTraveltime The maximimum travel time, i.e. the maximum time that the passengers may spend within a
     * vehicle. Must be >= directTraveltime.
     * @param directTraveltime The assumed direct travel time from pickupLocation to dropoffLocation.
     * @param passengerCount The number of passengers.
     * @param serviceDuration The duration of service, this duration occurs at pickup and dropoff.
     * @param sharingAllowed Whether sharing a vehicle with other passengers is permitted.
     **/
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