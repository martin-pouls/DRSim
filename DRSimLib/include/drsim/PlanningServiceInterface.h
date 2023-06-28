#pragma once
#include "PointLatLon.h"
#include "TripRequestData.h"
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {
/**
 * @brief API description of the planning service. This interface should be implemented by users of the simulation.
 **/
class PlanningServiceInterface {
public:
    virtual ~PlanningServiceInterface() = default;

    /**
     * @brief Called when a new trip request is submitted by the simulation.
     *
     * @param tripRequest The relevant trip request data.
     * @return Whether the trip request was accepted or not.
     **/
    virtual bool submitTripRequest(const TripRequestData& tripRequest) = 0;

    /**
     * @brief Called when the startup time of the simulation is finished. Enables the planning service to reset
     *evaluation data.
     **/
    virtual void finishStartup() = 0;

    /**
     * @brief Called when the pickup of a trip request is started.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param vehicleId The vehicle by which the action is performed.
     * @param requestId The ID of the relevant trip request.
     **/
    virtual void startPickup(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;

    /**
     * @brief Called when the pickup of a trip request is finished.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param vehicleId The vehicle by which the action is performed.
     * @param requestId The ID of the relevant trip request.
     **/
    virtual void endPickup(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;

    /**
     * @brief Called when the dropoff of a trip request is started.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param vehicleId The vehicle by which the action is performed.
     * @param requestId The ID of the relevant trip request.
     **/
    virtual void startDropoff(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;

    /**
     * @brief Called when the dropoff of a trip request is finished.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param vehicleId The vehicle by which the action is performed.
     * @param requestId The ID of the relevant trip request.
     **/
    virtual void endDropoff(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;

    /**
     * @brief Called periodically to update the location of the vehicle. By default this is called every second
     *(simulated time).
     *
     * @param timeStamp The current datetime of the simulation.
     * @param location The current vehicle location.
     * @param vehicleId The ID of the relevant vehicle.
     **/
    virtual void updateVehicleLocation(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                                       int vehicleId) = 0;

    /**
     * @brief Called when a new vehicle agent is created in the simulation.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param location The initial vehicle location.
     * @param capacity The capacity of the vehicle. The vehicle is assumed to be initially empty.
     * @param vehicleId The ID of the relevant vehicle.
     **/
    virtual void createVehicle(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                               unsigned capacity, int vehicleId) = 0;

    /**
     * @brief Called when a new vehicle agent is destroyed in the simulation.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param vehicleId The ID of the relevant vehicle.
     **/
    virtual void removeVehicle(const boost::posix_time::ptime& timeStamp, int vehicleId) = 0;

    /**
     * @brief Called when a vehicle finishes a repositioning movement.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param vehicleId The ID of the relevant vehicle.
     **/
    virtual void finishRepositioning(const boost::posix_time::ptime& timeStamp, int vehicleId) = 0;

    /**
     * @brief Called to update the next routable location of a vehicle. When a vehicle is driving along a road segment,
     * it cannot change its direction from its current location, but only from the next node in the road network (e.g. an
     * intersection). We refer to this as a routable location. This function is called whenever a vehicle starts driving
     * along a new arc in the road network.
     *
     * @param timeStamp The current datetime of the simulation.
     * @param location The next routable location.
     * @param arrivalTime The arrival datetime at the location.
     * @param vehicleId The ID of the relevant vehicle.
     **/
    virtual void updateNextRoutableLocation(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                                            const boost::posix_time::ptime& arrivalTime, int vehicleId) = 0;
};
} // namespace drsim