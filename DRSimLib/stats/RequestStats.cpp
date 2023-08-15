#include "include/drsim/RequestStats.h"

namespace drsim {
RequestStats::RequestStats(const TripRequestData& tripRequestData, bool accepted)
    : tripRequestData(tripRequestData)
    , accepted(accepted)
    , pickupTime(boost::posix_time::not_a_date_time)
    , dropoffTime(boost::posix_time::not_a_date_time)
    , requestLog() {
    requestLog.push_back(RequestLogEntry(tripRequestData.getId(), tripRequestData.getRequestTime(),
                                         accepted ? RequestState::ACCEPTED : RequestState::REJECTED));
}

void RequestStats::setPickupTime(const boost::posix_time::ptime& pickupTime) {
    this->pickupTime = pickupTime;
    requestLog.push_back(RequestLogEntry(tripRequestData.getId(), pickupTime, RequestState::PICKED_UP));
}

void RequestStats::setDropoffTime(const boost::posix_time::ptime& dropoffTime) {
    this->dropoffTime = dropoffTime;
    requestLog.push_back(RequestLogEntry(tripRequestData.getId(), dropoffTime, RequestState::DROPPED_OFF));
}

const std::vector<RequestLogEntry>& RequestStats::getRequestLog() const {
    return requestLog;
}

bool RequestStats::isPickedUp() const {
    return pickupTime != boost::posix_time::not_a_date_time;
}

bool RequestStats::isDroppedOff() const {
    return dropoffTime != boost::posix_time::not_a_date_time;

}

bool RequestStats::isAccepted() const {
    return accepted;
}

boost::posix_time::time_duration RequestStats::getWaitingTime() const {
    return pickupTime - tripRequestData.getRequestTime();
}

boost::posix_time::time_duration RequestStats::getRideTime() const {
    return (dropoffTime - pickupTime) - (tripRequestData.getServiceDuration() + tripRequestData.getServiceDuration());
}

boost::posix_time::time_duration RequestStats::getDelay() const {
    return getRideTime() - tripRequestData.getDirectTraveltime();
}
} // namespace drsim