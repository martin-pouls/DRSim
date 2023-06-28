#pragma once
#include "PointLatLon.h"

namespace drsim {
class VehicleData {
public:
    /**
     * @param id The unique identifier of the vehicle.
     * @param location The initial location.
     * @param capacity The capacity, i.e. the number of possible passengers (not including the driver).
     **/
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