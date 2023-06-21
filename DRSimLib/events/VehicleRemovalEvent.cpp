#include "VehicleRemovalEvent.h"
#include "include/drsim/VehicleManager.h"
#include "core/Constants.h"

namespace drsim {
VehicleRemovalEvent::VehicleRemovalEvent(const boost::posix_time::ptime& creationTime,
                                         const boost::posix_time::ptime& executionTime, VehicleManager& vehicleManager,
                                         int vehicleId)
    : Event(Constants::VEHICLE_REMOVAL_EVENT_PRIORITY, creationTime, executionTime)
    , vehicleManager(vehicleManager)
    , vehicleId(vehicleId) {
}

void VehicleRemovalEvent::execute() {
    vehicleManager.removeVehicle(vehicleId);
}
} // namespace drsim
