#pragma once
#include "include/drsim/Event.h"

namespace drsim {

class PlanningServiceInterface;

class StartupFinishEvent : public Event {
public:
    StartupFinishEvent(const boost::posix_time::ptime& creationTime, const boost::posix_time::ptime& executionTime,
                       PlanningServiceInterface& planningService);

    void execute() override;

private:
    PlanningServiceInterface& planningService;
};

} // namespace fzi::ridesharing::sim
