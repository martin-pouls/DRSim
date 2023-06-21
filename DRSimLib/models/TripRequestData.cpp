#include "include/drsim/TripRequestData.h"

namespace drsim {

TripRequestData::TripRequestData(int id, const PointLatLon& pickupLocation, const PointLatLon& dropoffLocation,
                                 const boost::posix_time::ptime& requestTime,
                                 const boost::posix_time::ptime& earliestPickupTime,
                                 const boost::posix_time::ptime& latestPickupTime,
                                 const boost::posix_time::time_duration& maximumTraveltime,
                                 const boost::posix_time::time_duration& directTraveltime, unsigned passengerCount,
                                 const boost::posix_time::time_duration& serviceDuration, bool sharingAllowed)
    : id(id)
    , pickupLocation(pickupLocation)
    , dropoffLocation(dropoffLocation)
    , requestTime(requestTime)
    , earliestPickupTime(earliestPickupTime)
    , latestPickupTime(latestPickupTime)
    , maximumTraveltime(maximumTraveltime)
    , directTraveltime(directTraveltime)
    , passengerCount(passengerCount)
    , serviceDuration(serviceDuration)
    , sharingAllowed(sharingAllowed) {
}

int TripRequestData::getId() const {
    return id;
}

const PointLatLon& TripRequestData::getPickupLocation() const {
    return pickupLocation;
}

const PointLatLon& TripRequestData::getDropoffLocation() const {
    return dropoffLocation;
}

const boost::posix_time::ptime& TripRequestData::getRequestTime() const {
    return requestTime;
}

const boost::posix_time::ptime& TripRequestData::getEarliestPickupTime() const {
    return earliestPickupTime;
}

const boost::posix_time::ptime& TripRequestData::getLatestPickupTime() const {
    return latestPickupTime;
}

const boost::posix_time::time_duration& TripRequestData::getMaximumTraveltime() const {
    return maximumTraveltime;
}

const boost::posix_time::time_duration& TripRequestData::getDirectTraveltime() const {
    return directTraveltime;
}

unsigned TripRequestData::getPassengerCount() const {
    return passengerCount;
}

const boost::posix_time::time_duration& TripRequestData::getServiceDuration() const {
    return serviceDuration;
}

bool TripRequestData::isSharingAllowed() const {
    return sharingAllowed;
}

} // namespace drsim