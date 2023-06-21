#pragma once
#include <boost/date_time/posix_time/ptime.hpp>
#include "Route.h"

namespace drsim {

class RoutingEngineInterface {
public:
    virtual ~RoutingEngineInterface() = default;
    virtual Route calculateRoute(const PointLatLon& origin, const PointLatLon& destination,
                                 boost::posix_time::ptime time) = 0;
};
} // namespace drsim