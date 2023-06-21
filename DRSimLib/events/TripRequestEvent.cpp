#include "TripRequestEvent.h"
#include "core/Constants.h"
#include "include/drsim/TripRequestManager.h"

namespace drsim {
TripRequestEvent::TripRequestEvent(const boost::posix_time::ptime& creationTime,
                                   const boost::posix_time::ptime& executionTime,
                                   const TripRequestData& tripRequestData, TripRequestManager& tripRequestManager)
    : Event(Constants::REQUEST_EVENT_PRIORITY, creationTime, executionTime)
    , tripRequestData(tripRequestData)
    , tripRequestManager(tripRequestManager) {
}

void TripRequestEvent::execute() {
    tripRequestManager.submitTripRequest(tripRequestData);
}
} // namespace drsim
