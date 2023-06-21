#include "VehicleCreationEvent.h"
#include "include/drsim/VehicleManager.h"
#include "core/Constants.h"

namespace drsim {
VehicleCreationEvent::VehicleCreationEvent(const boost::posix_time::ptime& creationTime,
                                           const boost::posix_time::ptime& executionTime,
                                           const VehicleData& vehicleData, VehicleManager& vehicleManager)
    : Event(Constants::VEHICLE_CREATION_EVENT_PRIORITY, creationTime, executionTime)
    , vehicleData(vehicleData)
    , vehicleManager(vehicleManager) {
}

void VehicleCreationEvent::execute() {
    vehicleManager.createVehicle(vehicleData);
}
} // namespace drsim
