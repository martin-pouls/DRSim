#pragma once
#include "include/drsim/Event.h"
#include "include/drsim/TripRequestData.h"

namespace drsim {

class TripRequestManager;

class TripRequestEvent : public Event {
public:
    TripRequestEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                     const TripRequestData& requestData, TripRequestManager& requestManager);

    void execute() override;

private:
    TripRequestData tripRequestData;
    TripRequestManager& tripRequestManager;
};

} // namespace drsim
