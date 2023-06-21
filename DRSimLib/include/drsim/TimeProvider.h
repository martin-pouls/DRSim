#pragma once
#include "TimeObserver.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace drsim {
class TimeProvider {
public:
    virtual ~TimeProvider() = default;
    virtual const boost::posix_time::ptime& getTime() const = 0;
    void registerTimeObserver(TimeObserver* observer);

private:
    std::vector<TimeObserver*> observers;

protected:
    void notifyTimeObservers();
};
} // namespace drsim