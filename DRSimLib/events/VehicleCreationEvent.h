#pragma once
#include "include/drsim/Event.h"
#include "include/drsim/VehicleData.h"

namespace drsim {

class VehicleManager;

class VehicleCreationEvent : public Event {
public:
    VehicleCreationEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                         const VehicleData& vehicleData, VehicleManager& vehicleManager);

    void execute() override;

private:
    VehicleData vehicleData;
    VehicleManager& vehicleManager;
};

} // namespace drsim
