#pragma once
#include "PointLatLon.h"

namespace drsim {
class VehicleData {
public:
    VehicleData(int id, const PointLatLon& location, unsigned capacity);

    int getId() const;
    const PointLatLon& getLocation() const;
    unsigned getCapacity() const;

private:
    int id;
    PointLatLon location;
    unsigned capacity;
};
} // namespace drsim