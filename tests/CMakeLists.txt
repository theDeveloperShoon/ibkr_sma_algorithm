enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(unit_tests
	unit/test_sma.cpp
	unit/test_backtester.cpp
	unit/test_movingaverage.cpp
)

target_link_libraries(unit_tests PRIVATE DEV_ALGO_CORE GTest::gtest_main)

add_executable(integration_tests
	integration/integration_backtester.cpp
)

target_link_libraries(integration_tests PRIVATE DEV_ALGO_CORE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
gtest_discover_tests(integration_tests)