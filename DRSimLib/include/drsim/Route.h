#pragma once
#include "RouteArc.h"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include <vector>

namespace drsim {

/**
 * @bried A route through the (road) network.
 **/
class Route {
public:
    /**
     * @param arcs The arcs of the route, should contain at least one arc.
     * @param duration The total duration of the route.
     **/
    Route(const std::vector<RouteArc>& arcs, const boost::posix_time::time_duration& duration);

    const boost::posix_time::time_duration& getDuration() const;
    const std::vector<RouteArc>& getArcs() const;

    /**
     * @brief Removes the first arc of the route.
     *
     * @return The removed arc.
     **/
    RouteArc popArc();

private:
    std::vector<RouteArc> arcs;
    boost::posix_time::time_duration duration;
};
} // namespace drsim