#pragma once
#include <drsim/Event.h>

namespace drsim {
class MockEvent : public Event {
public:
    MockEvent(int priority, const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime, bool& executed)
        : Event(priority, creationTime, executionTime)
        , executed(executed) {
    }

    void execute() override {
        executed = true;
    }

    bool& executed;
};
} // namespace drsim
