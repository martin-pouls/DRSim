#include "include/drsim/Route.h"

namespace drsim {
Route::Route(const std::vector<RouteArc>& arcs, const boost::posix_time::time_duration& duration)
    : arcs(arcs)
    , duration(duration) {
}

const boost::posix_time::time_duration& Route::getDuration() const {
    return duration;
}

const std::vector<RouteArc>& Route::getArcs() const {
    return arcs;
}

RouteArc Route::popArc() {
    RouteArc arc = arcs.at(0);
	arcs.erase(arcs.begin());
	return arc;
}
} // namespace drsim