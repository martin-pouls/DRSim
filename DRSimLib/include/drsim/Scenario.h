#pragma once
#include "TripRequestData.h"
#include "VehicleData.h"
#include <boost/date_time/posix_time/ptime.hpp>
#include <vector>

namespace drsim {

/**
 * @brief Specifies a simulation scenario.
 **/
class Scenario {
public:
    /**
     * @param start The start datetime of the scenario.
     * @param end The end datetime of the scenario. The simulation will stop at this time.
     * @param startupDuration The simulated time duration after which finishStartup() is called in the planning service.
     * @param tripRequests The trip requests for the scenario. These requests are submitted by the simulation to the
     * planning service.
     * @param vehicles The vehicle fleet for the scenario. All vehicles are assumed to be initially idle.
     **/
    Scenario(const boost::posix_time::ptime& start, const boost::posix_time::ptime& end,
             const boost::posix_time::time_duration& startupDuration, const std::vector<TripRequestData>& tripRequests,
             const std::vector<VehicleData> vehicles);

    const boost::posix_time::ptime& getStart() const;
    const boost::posix_time::ptime& getEnd() const;
    const boost::posix_time::time_duration& getStartupDuration() const;
    const std::vector<TripRequestData> getTripRequests() const;
    const std::vector<VehicleData> getVehicles() const;

private:
    boost::posix_time::ptime start;
    boost::posix_time::ptime end;
    boost::posix_time::time_duration startupDuration;
    std::vector<TripRequestData> tripRequests;
    std::vector<VehicleData> vehicles;
};
} // namespace drsim