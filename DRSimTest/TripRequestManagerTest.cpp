#include <gtest/gtest.h>
#include <drsim/TripRequestManager.h>
#include "utility/MockPlanningService.h"
#include <drsim/SimulationStats.h>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace drsim;

class TripRequestManagerTest : public ::testing::Test {};

TEST_F(TripRequestManagerTest, testSubmitTripRequest) {
    SimulationStats stats(boost::posix_time::from_iso_string("20000101T000000"), boost::posix_time::from_iso_string("20000101T000000"));
    MockPlanningService service;
    TripRequestManager manager(service, stats);

    TripRequestData request(0, PointLatLon(0, 0), PointLatLon(1, 0), boost::posix_time::from_iso_string("20000101T000000"),
        boost::posix_time::from_iso_string("20000101T000000"), boost::posix_time::from_iso_string("20000101T000010"),
        boost::posix_time::seconds(20), boost::posix_time::seconds(10), 2, boost::posix_time::seconds(1), true);
    manager.submitTripRequest(request);

    ASSERT_EQ(service.numRequests, 1);
}