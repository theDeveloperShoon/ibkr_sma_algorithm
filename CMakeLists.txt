# CMakeList.txt : CMake project for IBKR_CMAKE_MEAN_REVERSION, include source and define
# project specific logic here.

# Enable Hot Reload for MSVC compilers if supported.
if(MSVC)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>")
endif()

cmake_minimum_required (VERSION 3.25)
project (IBKR_SMA_ALGORITHM LANGUAGES CXX)

# Enforcingn mordern C++ standard
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include (FetchContent)

# Find vcpkg packages
find_package (protobuf CONFIG REQUIRED)
find_package (unofficial-intelrdfpmathlib CONFIG REQUIRED)
find_package (Threads REQUIRED)
find_package (cpr CONFIG REQUIRED)
find_package (glaze CONFIG REQUIRED)
find_package (magic_enum CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(apps)

# TODO: Add tests and install targets if needed.
