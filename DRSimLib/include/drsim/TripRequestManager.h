#pragma once

namespace drsim {
class PlanningServiceInterface;
class TripRequestData;
class SimulationStats;

class TripRequestManager {
public:
    TripRequestManager(PlanningServiceInterface& planningServiceInterface, SimulationStats& simulationLog);

    void submitTripRequest(const TripRequestData& tripRequestData);

private:
    PlanningServiceInterface& planningServiceInterface;
    SimulationStats& simulationStats;
};
} // namespace drsim