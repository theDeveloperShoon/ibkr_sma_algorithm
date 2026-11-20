enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(unit_tests
	unit/test_sma.cpp
	unit/test_backtester.cpp
	unit/test_movingaverage.cpp
	unit/test_sma_signals.cpp
)

target_link_libraries(unit_tests PRIVATE DEV_ALGO_CORE GTest::gtest_main)

add_executable(integration_tests
	integration/integration_backtester.cpp
)

target_link_libraries(integration_tests PRIVATE DEV_ALGO_CORE GTest::gtest_main)

# Optional local signing hook
option(ENABLE_LOCAL_SIGNING "Enable local signing for tests" ON)
set(SIGN_CERT_THUMBPRINT "8730AF125D9E89BC510E29599A696B62702DFAE4" CACHE STRING "Cert thumbprint used by signtool")

if(ENABLE_LOCAL_SIGNING)
	find_program(SIGNTOOL_EXE signtool REQUIRED)
	if(SIGN_CERT_THUMBPRINT STREQUAL "")
		message(FATAL_ERROR "SIGN_CERT_THUMBPRINT must be set when ENABLE_LOCAL_SIGNING is ON")
	endif()

	add_custom_command(TARGET integration_tests POST_BUILD
		COMMAND "${SIGNTOOL_EXE}" sign /sha1 "${SIGN_CERT_THUMBPRINT}" /fd SHA256 /tr http://timestamp.digicert.com /td SHA256 "$<TARGET_FILE:integration_tests>"
		VERBATIM
  )
endif()


include(GoogleTest)
gtest_discover_tests(unit_tests)
gtest_discover_tests(integration_tests)