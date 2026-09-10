set(TWSAPICPP_DIR "C:/TWS API/source/CppClient/client")

file(GLOB TWS_API_SOURCES 
	"${TWSAPICPP_DIR}/*.cpp"
#	"${TWSAPICPP_DIR}/protobuf/*.cc"
)

set(TWSAPIPROTO_DIR "C:/TWS API/source/proto")

file(GLOB TWS_API_PROTO_SOURCES
	"${TWSAPIPROTO_DIR}/*.proto"
)

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

add_library(dev_algo_core STATIC
	backtesting/BackTester.cpp
	backtesting/BackTester_SMA.cpp
	core/Utility.cpp
	ibkr/IBKR_Algo_Client.cpp
	sma/SMA.cpp
)

target_include_directories(dev_algo_core PUBLIC
	backtesting
	core
	ibkr
	sma
)

target_link_libraries(dev_algo_core PUBLIC
	tws_api
	protobuf::libprotobuf
	unofficial::intelrdfpmathlib::decimal128
	Threads::Threads
	cpr::cpr
	glaze::glaze
	magic_enum::magic_enum
	$<$<BOOL:${MSVC}>:ws2_32>
)

target_compile_options(dev_algo_core PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:
		/Zc:preprocessor /W4 /WX
	>
	$<$<NOT:$<BOOL:${MSVC}>>:
		-Wall -Wextra -pedantic -Werror
	>
)