#include "include/drsim/Scenario.h"

namespace drsim {

Scenario::Scenario(const boost::posix_time::ptime& start, const boost::posix_time::ptime& end,
                   const boost::posix_time::time_duration& startupDuration,
                   const std::vector<TripRequestData>& tripRequests, const std::vector<VehicleData> vehicles)
    : start(start)
    , end(end)
    , startupDuration(startupDuration)
    , tripRequests(tripRequests)
    , vehicles(vehicles) {
}

const boost::posix_time::ptime& Scenario::getStart() const {
    return start;
}

const boost::posix_time::ptime& Scenario::getEnd() const {
    return end;
}

const boost::posix_time::time_duration& Scenario::getStartupDuration() const {
    return startupDuration;
}

const std::vector<TripRequestData> Scenario::getTripRequests() const {
    return tripRequests;
}

const std::vector<VehicleData> Scenario::getVehicles() const {
    return vehicles;
}

} // namespace drsim