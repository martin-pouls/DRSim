#pragma once
#include <boost/date_time/posix_time/posix_time.hpp>

namespace drsim {
class TimeObserver {
public:
    virtual ~TimeObserver() = default;
    virtual void updateTime(const boost::posix_time::ptime& time) = 0;
};
} // namespace drsim
