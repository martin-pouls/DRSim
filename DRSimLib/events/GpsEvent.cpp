#include "GpsEvent.h"
#include "include/drsim/Vehicle.h"
#include "include/drsim/VehicleManager.h"
#include "core/Constants.h"

namespace drsim {

GpsEvent::GpsEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                   VehicleManager& vehicleManager)
    : Event(Constants::GPS_EVENT_PRIORITY, creationTime, executionTime)
    , vehicleManager(vehicleManager) {
}

void GpsEvent::execute() {
    vehicleManager.sendGpsMessages();
}

} // namespace drsim
