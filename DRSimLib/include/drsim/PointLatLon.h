#pragma once
#include <string>

namespace drsim {

/**
 * @brief Describes a point in latitude and longitude (WGS 84).
 **/
class PointLatLon {
public:
    PointLatLon(double latitude, double longitude);
    double getLatitude() const;
    double getLongitude() const;

    /**
     * @return A string representation of the point, e.g. (49.013304, 8.404207)
     **/
    std::string toString() const;
    bool operator==(const PointLatLon& other) const;

private:
    double latitude;
    double longitude;
};
} // namespace drsim