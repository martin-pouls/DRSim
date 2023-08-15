#pragma once
#include "TripRequestData.h"
#include "RequestLogEntry.h"
#include <vector>
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {
class RequestStats {
public:
    RequestStats(const TripRequestData& tripRequestData, bool accepted);

    void setPickupTime(const boost::posix_time::ptime& pickupTime);
    void setDropoffTime(const boost::posix_time::ptime& dropoffTime);
    const std::vector<RequestLogEntry>& getRequestLog() const;
    bool isPickedUp() const;
    bool isDroppedOff() const;
    bool isAccepted() const;
    boost::posix_time::time_duration getWaitingTime() const;
    boost::posix_time::time_duration getRideTime() const;
    boost::posix_time::time_duration getDelay() const;

private:
    TripRequestData tripRequestData;
    bool accepted;
    boost::posix_time::ptime pickupTime;
    boost::posix_time::ptime dropoffTime;
    std::vector<RequestLogEntry> requestLog;
};
} // namespace drsim