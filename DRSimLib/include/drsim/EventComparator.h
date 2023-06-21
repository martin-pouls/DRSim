#pragma once
#include "Event.h"
#include <memory>

namespace drsim {

struct EventComparator {
    bool operator()(const std::unique_ptr<Event>& e1, const std::unique_ptr<Event>& e2) const {
        if (e1->getExecutionTime() != e2->getExecutionTime()) {
            return e1->getExecutionTime() < e2->getExecutionTime();
        }
        if (e1->getPriority() != e2->getPriority()) {
            return e1->getPriority() > e2->getPriority();
        }
        return e1->getId() < e2->getId();
    }
};

} // namespace drsim