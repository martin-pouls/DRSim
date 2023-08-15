#include "utility/EuclideanRouter.h"
#include "utility/MockPlanningService.h"
#include <drsim/Engine.h>
#include <drsim/SimulationStats.h>
#include <drsim/Vehicle.h>
#include <gtest/gtest.h>

using namespace drsim;

class VehicleTest : public ::testing::Test {
public:
    VehicleTest()
        : vehicleData(0, PointLatLon(0, 0), 4)
        , start(boost::posix_time::from_iso_string("20000101T000000"))
        , end(boost::posix_time::from_iso_string("20000101T010000")) {
    }

    VehicleData vehicleData;
    boost::posix_time::ptime start;
    boost::posix_time::ptime end;
};

TEST_F(VehicleTest, testTour) {
    Engine engine(start);
    SimulationStats stats(start, end);
    MockPlanningService planningService;
    EuclideanRouter routingEngine;
    Vehicle vehicle(vehicleData, planningService, routingEngine, engine, stats);

    TripRequestData request0(0, PointLatLon(1, 0), PointLatLon(4, 0), boost::posix_time::from_iso_string("20000101T000000"),
        boost::posix_time::from_iso_string("20000101T000000"), boost::posix_time::from_iso_string("20000101T000100"),
        boost::posix_time::seconds(20), boost::posix_time::seconds(10), 2, boost::posix_time::seconds(1), true);

    TripRequestData request1(1, PointLatLon(2, 0), PointLatLon(3, 0), boost::posix_time::from_iso_string("20000101T000000"),
        boost::posix_time::from_iso_string("20000101T000010"), boost::posix_time::from_iso_string("20000101T000100"),
        boost::posix_time::seconds(20), boost::posix_time::seconds(10), 2, boost::posix_time::seconds(1), true);

    stats.addRequestStats(request0, true);
    stats.addRequestStats(request1, true);

    std::vector<TourStop> tour = {
        TourStop(0, TourStopAction::PICKUP, PointLatLon(1, 0), boost::posix_time::from_iso_string("20000101T000000"),
                 boost::posix_time::from_iso_string("20000101T000002"), boost::posix_time::seconds(1), 2),
        TourStop(1, TourStopAction::PICKUP, PointLatLon(2, 0), boost::posix_time::from_iso_string("20000101T000010"),
                 boost::posix_time::from_iso_string("20000101T000011"), boost::posix_time::seconds(1), 2),
        TourStop(1, TourStopAction::DROPOFF, PointLatLon(3, 0), boost::posix_time::from_iso_string("20000101T000000"),
                 boost::posix_time::from_iso_string("20000101T000013"), boost::posix_time::seconds(1), 2),
        TourStop(0, TourStopAction::DROPOFF, PointLatLon(4, 0), boost::posix_time::from_iso_string("20000101T000020"),
                 boost::posix_time::from_iso_string("20000101T000021"), boost::posix_time::seconds(1), 2)};

    vehicle.assignTour(tour);

    engine.runUntil(boost::posix_time::from_iso_string("20000101T000009"));
    ASSERT_EQ(planningService.numPickupStarts, 1);
    ASSERT_EQ(planningService.numPickupEnds, 1);
    ASSERT_EQ(planningService.numDropoffStarts, 0);
    ASSERT_EQ(planningService.numDropoffEnds, 0);
    ASSERT_EQ(vehicle.getLocation(), PointLatLon(2, 0));

    engine.runUntil(boost::posix_time::from_iso_string("20000101T000012"));
    ASSERT_EQ(planningService.numPickupStarts, 2);
    ASSERT_EQ(planningService.numPickupEnds, 2);
    ASSERT_EQ(planningService.numDropoffStarts, 1);
    ASSERT_EQ(planningService.numDropoffEnds, 0);
    ASSERT_EQ(vehicle.getLocation(), PointLatLon(3, 0));

    engine.run();
    ASSERT_EQ(planningService.numPickupStarts, 2);
    ASSERT_EQ(planningService.numPickupEnds, 2);
    ASSERT_EQ(planningService.numDropoffStarts, 2);
    ASSERT_EQ(planningService.numDropoffEnds, 2);
    ASSERT_EQ(vehicle.getLocation(), PointLatLon(4, 0));
}

TEST_F(VehicleTest, testRepositioning) {
    Engine engine(start);
    SimulationStats stats(start, end);
    MockPlanningService planningService;
    EuclideanRouter routingEngine;
    Vehicle vehicle(vehicleData, planningService, routingEngine, engine, stats);

    vehicle.assignRepositioning(PointLatLon(10, 0));
    
    engine.runUntil(boost::posix_time::from_iso_string("20000101T000009"));
    ASSERT_EQ(planningService.numRepositioningsFinished, 0);

    engine.runUntil(boost::posix_time::from_iso_string("20000101T000010"));
    ASSERT_EQ(planningService.numRepositioningsFinished, 1);
    ASSERT_EQ(vehicle.getLocation(), PointLatLon(10, 0));

    vehicle.assignRepositioning(PointLatLon(0, 0));

    engine.runUntil(boost::posix_time::from_iso_string("20000101T000015"));
    ASSERT_EQ(planningService.numRepositioningsFinished, 1);

    TripRequestData request0(0, PointLatLon(0, 0), PointLatLon(1, 0), boost::posix_time::from_iso_string("20000101T000000"),
        boost::posix_time::from_iso_string("20000101T000000"), boost::posix_time::from_iso_string("20000101T000100"),
        boost::posix_time::seconds(20), boost::posix_time::seconds(10), 2, boost::posix_time::seconds(1), true);

    stats.addRequestStats(request0, true);

    std::vector<TourStop> tour = {
        TourStop(0, TourStopAction::PICKUP, PointLatLon(0, 0), boost::posix_time::from_iso_string("20000101T000000"),
                 boost::posix_time::from_iso_string("20000101T000021"), boost::posix_time::seconds(1), 2),
        TourStop(0, TourStopAction::DROPOFF, PointLatLon(1, 0), boost::posix_time::from_iso_string("20000101T000000"),
                 boost::posix_time::from_iso_string("20000101T000023"), boost::posix_time::seconds(1), 2)};
    vehicle.assignTour(tour);

    engine.run();
    ASSERT_EQ(planningService.numPickupStarts, 1);
    ASSERT_EQ(planningService.numPickupEnds, 1);
    ASSERT_EQ(planningService.numDropoffStarts, 1);
    ASSERT_EQ(planningService.numDropoffEnds, 1);
    ASSERT_EQ(planningService.numRepositioningsFinished, 1);
    ASSERT_EQ(vehicle.getLocation(), PointLatLon(1, 0));
}