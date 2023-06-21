#include "utility/MockEvent.h"
#include <drsim/Engine.h>
#include <gtest/gtest.h>

using namespace drsim;

class EngineTest : public ::testing::Test {};

TEST_F(EngineTest, testEvents) {
    Engine engine(boost::posix_time::from_iso_string("20000101T000000"));
    bool executed[2] = {false, false};

    std::unique_ptr<Event> event =
        std::make_unique<MockEvent>(1, engine.getTime(), boost::posix_time::from_iso_string("20000101T010000"), executed[0]);
    const Event* event1 = engine.add(event);

    event = std::make_unique<MockEvent>(1, engine.getTime(), boost::posix_time::from_iso_string("20000101T020000"), executed[1]);
    const Event* event2 = engine.add(event);

    engine.run();

    ASSERT_TRUE(executed[0]);
    ASSERT_TRUE(executed[1]);
}

TEST_F(EngineTest, testPriority) {
    Engine engine(boost::posix_time::from_iso_string("20000101T000000"));
    bool executed[2] = {false, false};

    std::unique_ptr<Event> event =
        std::make_unique<MockEvent>(0, engine.getTime(), boost::posix_time::from_iso_string("20000101T010000"), executed[0]);
    const Event* event1 = engine.add(event);

    event = std::make_unique<MockEvent>(1, engine.getTime(), boost::posix_time::from_iso_string("20000101T010000"), executed[1]);
    const Event* event2 = engine.add(event);

    engine.step();
    ASSERT_FALSE(executed[0]);
    ASSERT_TRUE(executed[1]);

    engine.step();
    ASSERT_TRUE(executed[0]);
    ASSERT_TRUE(executed[1]);
}

TEST_F(EngineTest, testExecutionTime) {
    Engine engine(boost::posix_time::from_iso_string("20000101T000000"));
    bool executed[2] = {false, false};

    std::unique_ptr<Event> event =
        std::make_unique<MockEvent>(1, engine.getTime(), boost::posix_time::from_iso_string("20000101T010000"), executed[0]);
    const Event* event1 = engine.add(event);

    event = std::make_unique<MockEvent>(1, engine.getTime(), boost::posix_time::from_iso_string("20000101T020000"), executed[1]);
    const Event* event2 = engine.add(event);

    engine.runUntil(boost::posix_time::from_iso_string("20000101T013000"));
    ASSERT_TRUE(executed[0]);
    ASSERT_FALSE(executed[1]);

    engine.runUntil(boost::posix_time::from_iso_string("20000101T023000"));
    ASSERT_TRUE(executed[0]);
    ASSERT_TRUE(executed[1]);
}

TEST_F(EngineTest, testRemove) {
    Engine engine(boost::posix_time::from_iso_string("20000101T000000"));
    bool executed[2] = {false, false};

    std::unique_ptr<Event> event =
        std::make_unique<MockEvent>(1, engine.getTime(), boost::posix_time::from_iso_string("20000101T010000"), executed[0]);
    const Event* event1 = engine.add(event);

    event = std::make_unique<MockEvent>(1, engine.getTime(), boost::posix_time::from_iso_string("20000101T020000"), executed[1]);
    const Event* event2 = engine.add(event);

    engine.runUntil(boost::posix_time::from_iso_string("20000101T013000"));
    ASSERT_TRUE(executed[0]);
    ASSERT_FALSE(executed[1]);

    engine.remove(*event2);

    engine.runUntil(boost::posix_time::from_iso_string("20000101T023000"));
    ASSERT_TRUE(executed[0]);
    ASSERT_FALSE(executed[1]);
}
