#pragma once
#include "include/drsim/Event.h"
#include "core/Constants.h"

namespace drsim {

class Vehicle;
class RouteArc;

class ArcEndEvent : public Event {
public:
    ArcEndEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                Vehicle& vehicle, RouteArc& arc);

    void execute() override;

private:
    Vehicle& vehicle;
    RouteArc& arc;
};

} // namespace drsim
