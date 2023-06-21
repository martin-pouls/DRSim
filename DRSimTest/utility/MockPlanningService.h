#pragma once
#include <drsim/PlanningServiceInterface.h>

namespace drsim {
class MockPlanningService : public PlanningServiceInterface {
public:
    MockPlanningService()
        : numRequests(0)
        , startUpFinished(false)
        , numPickupStarts(0)
        , numPickupEnds(0)
        , numDropoffStarts(0)
        , numDropoffEnds(0)
        , numLocationUpdates(0)
        , numVehiclesCreated(0)
        , numVehiclesRemoved(0)
        , numRepositioningsFinished(0)
        , numRouteableLocationUpdates(0) {
    }

    bool submitTripRequest(const TripRequestData& tripRequest) override {
        numRequests++;
        return true;
    }

    void finishStartup() override {
        startUpFinished = true;
    }

    void startPickup(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) override {
        numPickupStarts++;
    }

    void endPickup(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) override {
        numPickupEnds++;
    }

    void startDropoff(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) override {
        numDropoffStarts++;
    }

    void endDropoff(const boost::posix_time::ptime& timeStamp, int vehicleId, int requestId) override {
        numDropoffEnds++;
    }

    void updateVehicleLocation(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                               int vehicleId) override {
        numLocationUpdates++;
    }

    void createVehicle(const boost::posix_time::ptime& timeStamp, const PointLatLon& location, unsigned capacity,
                       int vehicleId) override {
        numVehiclesCreated++;
    }

    void removeVehicle(const boost::posix_time::ptime& timeStamp, int vehicleId) override {
        numVehiclesRemoved++;
    }

    void finishRepositioning(const boost::posix_time::ptime& timeStamp, int vehicleId) override {
        numRepositioningsFinished++;
    }

    void updateNextRoutableLocation(const boost::posix_time::ptime& timeStamp, const PointLatLon& location,
                                    const boost::posix_time::ptime& arrivalTime, int vehicleId) override {
        numRouteableLocationUpdates++;
    }

    unsigned numRequests;
    bool startUpFinished;
    unsigned numPickupStarts;
    unsigned numPickupEnds;
    unsigned numDropoffStarts;
    unsigned numDropoffEnds;
    unsigned numLocationUpdates;
    unsigned numVehiclesCreated;
    unsigned numVehiclesRemoved;
    unsigned numRepositioningsFinished;
    unsigned numRouteableLocationUpdates;
};
} // namespace drsim