cmake_minimum_required(VERSION 3.16)
project(RayTracer)

message(STATUS "C++ compiler: " ${CMAKE_CXX_COMPILER})

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE lib/)

add_custom_target(run "./${PROJECT_NAME}" DEPENDS ${PROJECT_NAME} USES_TERMINAL)
add_custom_target(render "eog" "render.ppm" DEPENDS run USES_TERMINAL)
