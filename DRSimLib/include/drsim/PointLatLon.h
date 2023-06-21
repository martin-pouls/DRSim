#pragma once
#include <string>

namespace drsim {
class PointLatLon {
public:
    PointLatLon(double latitude, double longitude);
    double getLatitude() const;
    double getLongitude() const;
    std::string toString() const;
    bool operator==(const PointLatLon& other) const;

private:
    double latitude;
    double longitude;
};
} // namespace drsim