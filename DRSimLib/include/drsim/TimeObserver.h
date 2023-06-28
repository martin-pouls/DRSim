#pragma once
#include <boost/date_time/posix_time/posix_time.hpp>

namespace drsim {

/**
 * @brief An observer that is notified whenever the time in the simulation changes.
 **/
class TimeObserver {
public:
    virtual ~TimeObserver() = default;

    /**
     * @brief Function that is called whenever the time in the simulation changes.
     * 
     * @param The current simulation time.
     **/
    virtual void updateTime(const boost::posix_time::ptime& time) = 0;
};
} // namespace drsim
