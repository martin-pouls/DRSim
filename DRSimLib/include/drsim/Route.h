#pragma once
#include "RouteArc.h"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include <vector>

namespace drsim {
class Route {
public:
    Route(const std::vector<RouteArc>& arcs, const boost::posix_time::time_duration& duration);

    const boost::posix_time::time_duration& getDuration() const;
    const std::vector<RouteArc>& getArcs() const;
    RouteArc popArc();

private:
    std::vector<RouteArc> arcs;
    boost::posix_time::time_duration duration;
};
} // namespace drsim