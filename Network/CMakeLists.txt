CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project (R-Type)

set(EXECUTABLE_SOURCE_DIR, {CMAKE_SOURCE_DIR})
set(HEADER_FILES ISocket.hh WSocket.hh USocket.hh)
set(SOURCES main.cpp WSocket.cpp USocket.cpp)

file(GLOB_RECURSE ${SOURCES} ${HEADER_FILES})

add_executable(R-Type ${SOURCES})