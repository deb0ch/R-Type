CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#PROJECT(test)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb3 -O0")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ECS)

SET(HEADERS
  IMutex.hh
  IThread.hpp
  ThreadException.hh
  UMutex.hh
  UThread.hpp
  WMutex.hh
  WThread.hpp
  )

SET(SOURCES
  ThreadException.cpp
  UMutex.cpp
  WMutex.cpp
  )

SET (LIB_TYPE STATIC)

FILE(GLOB_RECURSE ${SOURCES} ${HEADERS})
	
ADD_LIBRARY(Threadlib ${LIB_TYPE} ${HEADERS} ${SOURCES})

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (UNIX)

#ADD_EXECUTABLE(test main.cpp)

#TARGET_LINK_LIBRARIES(test Threadlib)
#TARGET_LINK_LIBRARIES(test pthread)
