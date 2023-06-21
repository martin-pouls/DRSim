#pragma once
#include "PointLatLon.h"
#include "TripRequestData.h"
#include <boost/date_time/posix_time/ptime.hpp>

namespace drsim {
class PlanningServiceInterface {
public:
    virtual ~PlanningServiceInterface() = default;

    virtual bool submitTripRequest(const TripRequestData& tripRequest) = 0;
    virtual void finishStartup() = 0;

    virtual void startPickup(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;
    virtual void endPickup(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;
    virtual void startDropoff(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;
    virtual void endDropoff(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) = 0;
    virtual void updateVehicleLocation(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                                       int vehicleId) = 0;
    virtual void createVehicle(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                               unsigned capacity, int vehicleId) = 0;
    virtual void removeVehicle(const boost::posix_time::ptime& timeStamp, int vehicleId) = 0;
    virtual void finishRepositioning(const boost::posix_time::ptime& timeStamp, int vehicleId) = 0;
    virtual void updateNextRoutableLocation(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                                            const boost::posix_time::ptime& arrivalTime, int vehicleId) = 0;
};
} // namespace drsim