CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project (R-Type)

set(EXECUTABLE_SOURCE_DIR, {CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(R-Type ${SOURCES})