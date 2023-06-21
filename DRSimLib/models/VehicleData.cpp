#include "include/drsim/VehicleData.h"

namespace drsim {
VehicleData::VehicleData(int id, const PointLatLon& location, unsigned capacity)
    : id(id)
    , location(location)
    , capacity(capacity) {
}

int VehicleData::getId() const {
    return id;
}

const PointLatLon& VehicleData::getLocation() const {
    return location;
}

unsigned VehicleData::getCapacity() const {
    return capacity;
}

} // namespace drsim