CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project (RType)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_SOURCE_DIR, {CMAKE_SOURCE_DIR})

add_subdirectory(Network)
add_subdirectory(ECS)
add_subdirectory(component)
add_subdirectory(systems)

# get_directory_property(SOURCES DIRECTORY Network DEFINITION SOURCES)
#get_directory_property(HEADER_FILES DIRECTORY Network DEFINITION HEADER_FILES)
#file(GLOB_RECURSE ${SOURCES} ${HEADER_FILES})

add_executable(RType ${SOURCES})
