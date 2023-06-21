#pragma once
#include "include/drsim/Event.h"
#include "include/drsim/TourStop.h"
#include <vector>

namespace drsim {

class Vehicle;

class TourUpdateEvent : public Event {
public:
    TourUpdateEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                    Vehicle& vehicle, const std::vector<TourStop>& tour);

    void execute() override;

private:
    Vehicle& vehicle;
    std::vector<TourStop> tour;
};

} // namespace drsim
