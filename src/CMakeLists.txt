set(TWSAPICPP_DIR "C:/TWS API/source/CppClient/client")
set(TWSAPIPROTO_DIR "C:/TWS API/source/proto")

if(BUILD_TWS_API)
	set(DEV_ALGO_SOURCES 
		backtesting/BackTester.cpp
		backtesting/BackTester_SMA.cpp
		ibkr/IBKR_Algo_Client.cpp
		core/Utility.cpp
		sma/SMA.cpp
		sma/OldSMA.cpp
	)

	file(GLOB TWS_API_SOURCES "${TWSAPICPP_DIR}/*.cpp")
	file(GLOB TWS_API_PROTO_SOURCES "${TWSAPIPROTO_DIR}/*.proto")

	add_library(tws_api STATIC ${TWS_API_SOURCES})

	if(TWS_API_PROTO_SOURCES)
	PROTOBUF_GENERATE(
		TARGET tws_api
		LANGUAGE cpp
		PROTOS ${TWS_API_PROTO_SOURCES}
		IMPORT_DIRS "${TWSAPIPROTO_DIR}"
	)
	#list(APPEND TWS_API_SOURCES ${TWS_API_PROTO_SRCS} ${TWS_API_PROTO_HDRS})
	endif()

	target_include_directories(tws_api PUBLIC ${TWSAPICPP_DIR} ${CMAKE_CURRENT_BINARY_DIR})
	target_link_libraries(tws_api PUBLIC protobuf::libprotobuf)
	target_compile_options(tws_api PUBLIC
	$<$<CXX_COMPILER_ID:MSVC>:
		/W3
		/wd4267
		/wd4244
		>
		$<$<NOT:$<BOOL:${MSVC}>>:
			-Wall -Wextra -pedantic -Werror
		>
	)

	list(APPEND DEV_ALGO_SOURCES ibkr/IBKR_Algo_Client.cpp)

	set(EXTRA_PUBLIC_LIBS tws_api protobuf::libprotobuf)
else()
	set(DEV_ALGO_SOURCES 
		backtesting/BackTester.cpp
		backtesting/BackTester_SMA.cpp
		core/Utility.cpp
		sma/SMA.cpp
		sma/OldSMA.cpp
	)

	set(EXTRA_PUBLIC_LIBS)
endif()

add_library(DEV_ALGO_CORE STATIC ${DEV_ALGO_SOURCES})
 

target_include_directories(DEV_ALGO_CORE PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	backtesting
	core
	ibkr
	sma
)

target_link_libraries(DEV_ALGO_CORE PUBLIC
	${EXTRA_PUBLIC_LIBS}
	unofficial::intelrdfpmathlib::decimal128
	Threads::Threads
	cpr::cpr
	glaze::glaze
	magic_enum::magic_enum
	$<$<BOOL:${MSVC}>:ws2_32>
)

if(BUILD_TWS_API)
	target_compile_definitions(DEV_ALGO_CORE PUBLIC BUILD_TWS_API=1)
else()
	target_compile_definitions(DEV_ALGO_CORE PUBLIC BUILD_TWS_API=0)
endif()

target_compile_options(DEV_ALGO_CORE PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:
		/Zc:preprocessor /W4 /WX
	>
	$<$<NOT:$<BOOL:${MSVC}>>:
		-Wall -Wextra -pedantic -Werror
	>
)