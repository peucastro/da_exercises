cmake_minimum_required(VERSION 3.28)
project(da2324_pLP_student)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_BUILD_TYPE "Release")
set(GOOGLETEST_PATH lib/googletest)

add_definitions(-DBUILD_DEPS=ON)

add_subdirectory(${GOOGLETEST_PATH})
include_directories(${GOOGLETEST_PATH}/googletest/include)
include_directories(${GOOGLETEST_PATH}/googlemock/include)

find_package(ortools QUIET)
if(NOT ortools_FOUND)
    message(FATAL_ERROR "OR-Tools not installed. Check this link: https://developers.google.com/optimization/install/cpp")
endif()

file(GLOB TPLP_FILES CONFIGURE_DEPENDS "TPLP/*.cpp")
add_executable(da2324_pLP_student ${TPLP_FILES})

target_link_libraries(da2324_pLP_student gtest gtest_main ortools::ortools)
