#pragma once
#include "include/drsim/Event.h"

namespace drsim {

class Vehicle;

class ServiceStartEvent : public Event {
public:
    ServiceStartEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                      Vehicle& vehicle);

    void execute() override;

private:
    Vehicle& vehicle;
};

} // namespace drsim
