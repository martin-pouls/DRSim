#pragma once
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {
inline boost::posix_time::ptime maxDateTime(const boost::posix_time::ptime& p1, const boost::posix_time::ptime& p2) {
    if (p1 >= p2) {
        return p1;
    }
    return p2;
}
} // namespace drsim