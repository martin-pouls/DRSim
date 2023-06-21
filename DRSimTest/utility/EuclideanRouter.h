#pragma once
#include <drsim/RoutingEngineInterface.h>

namespace drsim {
class EuclideanRouter : public RoutingEngineInterface {
    Route calculateRoute(const PointLatLon& origin, const PointLatLon& destination,
                         boost::posix_time::ptime time) override {

        unsigned distance = std::round(std::sqrt(std::pow(destination.getLatitude() - origin.getLatitude(), 2) +
                                                 std::pow(destination.getLongitude() - origin.getLongitude(), 2)));
        auto duration = boost::posix_time::seconds(distance);

        RouteArc arc(duration, distance, origin, destination, time, time + duration);
        return Route({arc}, duration);
    }
};
} // namespace drsim