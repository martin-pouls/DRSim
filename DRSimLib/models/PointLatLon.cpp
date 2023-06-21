#include "include/drsim/PointLatLon.h"
#include <sstream>
#include <iomanip>

namespace drsim {
PointLatLon::PointLatLon(double latitude, double longitude)
    : latitude(latitude)
    , longitude(longitude) {
}

double PointLatLon::getLatitude() const {
    return latitude;
}

double PointLatLon::getLongitude() const {
    return longitude;
}

std::string PointLatLon::toString() const {
    std::stringstream stream;
    stream << "(";
    stream << std::fixed << std::setprecision(6);
    stream << latitude << ", " << longitude << ")";
    return stream.str();
}

bool PointLatLon::operator==(const PointLatLon& other) const {
    return this->latitude == other.latitude && this->longitude == other.longitude;
}
} // namespace drsim