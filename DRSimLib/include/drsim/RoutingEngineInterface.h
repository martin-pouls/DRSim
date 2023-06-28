#pragma once
#include "Route.h"
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {

/**
 * @brief An interface to a routing engine. Users should provide an implementation (either an own routing engine or a
 * wrapper around existing solutions like OSRM, RoutingKit or Google Maps).
 **/
class RoutingEngineInterface {
public:
    virtual ~RoutingEngineInterface() = default;

    /**
     * @brief Calculates a route on the underyling (road) network.
     *
     * @param origin The origin of the route.
     * @param destination The destination of the route.
     * @param time The starting time of the route (relevant in case time-dependent travel times are considered).
     *
     * @return The calculated route, note that the route should contain at least one arc from the origin to destination.
     **/
    virtual Route calculateRoute(const PointLatLon& origin, const PointLatLon& destination,
                                 boost::posix_time::ptime time) = 0;
};
} // namespace drsim