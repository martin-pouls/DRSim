#include "StartupFinishEvent.h"
#include "core/Constants.h"
#include "include/drsim/PlanningServiceInterface.h"

namespace drsim {
StartupFinishEvent::StartupFinishEvent(const boost::posix_time::ptime& creationTime,
    const boost::posix_time::ptime& executionTime, PlanningServiceInterface& planningService):
    Event(Constants::STARTUP_FINISH_EVENT_PRIORITY, creationTime, executionTime),
    planningService(planningService)
{
}

void StartupFinishEvent::execute()
{
	planningService.finishStartup();
}

}
