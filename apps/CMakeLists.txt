add_executable(IBKR_SMA_ALGORITHM
	main.cpp
	main.h
)

target_link_libraries(IBKR_SMA_ALGORITHM PRIVATE dev_algo_core)

set_target_properties(IBKR_SMA_ALGORITHM PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_compile_definitions(IBKR_SMA_ALGORITHM PRIVATE 
	CSV_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_options(IBKR_SMA_ALGORITHM PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:
		/Zc:preprocessor /W4 /WX
	>
	$<$<NOT:$<BOOL:${MSVC}>>:
		-Wall -Wextra -pedantic -Werror
	>
)