#include "include/drsim/Event.h"

namespace drsim {

Event::Event(int priority, const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime)
    : id(-1)
    , priority(priority)
    , creationTime(creationTime)
    , executionTime(executionTime) {
}

int Event::getId() const {
    return id;
}

int Event::getPriority() const {
    return priority;
}

const boost::posix_time::ptime& Event::getExecutionTime() const {
    return executionTime;
}

void Event::setId(const int id) {
    this->id = id;
}
} // namespace drsim
