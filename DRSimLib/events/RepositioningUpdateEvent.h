#pragma once
#include "include/drsim/Event.h"
#include "include/drsim/PointLatLon.h"

namespace drsim {

class Vehicle;

class RepositioningUpdateEvent : public Event {
public:
    RepositioningUpdateEvent(const boost::posix_time::ptime& creationTime,
                             const boost::posix_time::ptime& executionTime, Vehicle& vehicle,
                             const PointLatLon& target);

    void execute() override;

private:
    Vehicle& vehicle;
    PointLatLon target;
};

} // namespace drsim
