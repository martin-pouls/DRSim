#pragma once
#include "include/drsim/Event.h"

namespace drsim {

class VehicleManager;

class VehicleRemovalEvent : public Event {
public:
    VehicleRemovalEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                        VehicleManager& vehicleManager, int vehicleId);

    void execute() override;

private:
    VehicleManager& vehicleManager;
    int vehicleId;
};

} // namespace drsim
