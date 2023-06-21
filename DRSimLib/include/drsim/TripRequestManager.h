#pragma once

namespace drsim {
class PlanningServiceInterface;
class TripRequestData;
class SimulationLog;

class TripRequestManager {
public:
    TripRequestManager(PlanningServiceInterface& planningServiceInterface, SimulationLog& simulationLog);

    void submitTripRequest(const TripRequestData& tripRequestData);

private:
    PlanningServiceInterface& planningServiceInterface;
    SimulationLog& simulationLog;
};
} // namespace drsim