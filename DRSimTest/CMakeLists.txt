enable_testing()

add_executable(DrSimTest 
"utility/EuclideanRouter.h"
"utility/MockEvent.h" 
"utility/MockPlanningService.h" 
"EngineTest.cpp" 
"TripRequestManagerTest.cpp" 
"VehicleManagerTest.cpp" 
"VehicleTest.cpp" 
)

find_package(GTest REQUIRED)
target_link_libraries(DrSimTest GTest::gtest GTest::gtest_main DRSimLib)
