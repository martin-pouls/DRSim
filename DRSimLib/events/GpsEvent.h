#pragma once
#include "include/drsim/Event.h"

namespace drsim {

class VehicleManager;

class GpsEvent : public Event {
public:
    GpsEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
             VehicleManager& vehicle);

    void execute() override;

private:
    VehicleManager& vehicleManager;
};

} // namespace drsim
