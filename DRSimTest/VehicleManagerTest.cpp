#include <gtest/gtest.h>
#include <drsim/VehicleManager.h>
#include "utility/EuclideanRouter.h"
#include "utility/MockPlanningService.h"
#include <drsim/Engine.h>
#include <drsim/SimulationLog.h>

using namespace drsim;

class VehicleManagerTest : public ::testing::Test {
public:
    VehicleManagerTest()
        : vehicleData0(0, PointLatLon(0, 0), 4)
        , vehicleData1(1, PointLatLon(0, 0), 4)
        , start(boost::posix_time::from_iso_string("20000101T000000"))
        , end(boost::posix_time::from_iso_string("20000101T010000")) {
    }

    VehicleData vehicleData0;
    VehicleData vehicleData1;
    boost::posix_time::ptime start;
    boost::posix_time::ptime end;
};

TEST_F(VehicleManagerTest, testCreateVehicle) {
    Engine engine(start);
    SimulationLog log(start, end);
    MockPlanningService planningService;
    EuclideanRouter routingEngine;

    VehicleManager manager(planningService, routingEngine, engine, log);
    manager.createVehicle(vehicleData0);

    ASSERT_EQ(planningService.numVehiclesCreated, 1);
}

TEST_F(VehicleManagerTest, testRemoveVehicle) {
    Engine engine(start);
    SimulationLog log(start, end);
    MockPlanningService planningService;
    EuclideanRouter routingEngine;

    VehicleManager manager(planningService, routingEngine, engine, log);
    manager.createVehicle(vehicleData0);

    ASSERT_EQ(planningService.numVehiclesCreated, 1);
    ASSERT_EQ(planningService.numVehiclesRemoved, 0);

    manager.removeVehicle(0);
    ASSERT_EQ(planningService.numVehiclesCreated, 1);
    ASSERT_EQ(planningService.numVehiclesRemoved, 1);
}

TEST_F(VehicleManagerTest, testSendGpsMessage) {
    Engine engine(start);
    SimulationLog log(start, end);
    MockPlanningService planningService;
    EuclideanRouter routingEngine;

    VehicleManager manager(planningService, routingEngine, engine, log);
    manager.createVehicle(vehicleData0);
    manager.createVehicle(vehicleData1);

    manager.sendGpsMessages();

    ASSERT_EQ(planningService.numLocationUpdates, 2);
}