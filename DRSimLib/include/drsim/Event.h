#pragma once
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {

class Event {
public:
    virtual ~Event() = default;
    Event(int priority, const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime);

    virtual void execute() = 0;
    int getId() const;
    int getPriority() const;
    const boost::posix_time::ptime& getExecutionTime() const;
    void setId(const int id);

protected:
    int id;
    int priority;
    boost::posix_time::ptime creationTime;
    boost::posix_time::ptime executionTime;
};

} // namespace drsim
