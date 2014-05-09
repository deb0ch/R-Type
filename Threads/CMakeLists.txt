CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#PROJECT(test)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb3 -O0")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ECS)

SET(HEADERS
  IMutex.hh
  IThread.hpp
  ThreadException.hh
  MutexException.hh
  UMutex.hh
  UThread.hpp
  WMutex.hh
  WThread.hpp
  ThreadPool.hpp
  ScopedMutex.hh
  Threads.hh
  TasksFifo.hpp
  ICondVar.hh
  UCondVar.hh)

SET(SOURCES
  ThreadException.cpp
  MutexException.cpp
  UMutex.cpp
  WMutex.cpp
  ScopedMutex.cpp
  UCondVar.cpp
  main.cpp)

SET (LIB_TYPE STATIC)

#FILE(GLOB_RECURSE ${SOURCES} ${HEADERS})
	
#ADD_LIBRARY(Threadlib ${LIB_TYPE} ${HEADERS} ${SOURCES})
ADD_EXECUTABLE(Threadlib ${HEADERS} ${SOURCES})

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	INCLUDE_DIRECTORIES(/usr/include/)
	TARGET_LINK_LIBRARIES(Threadlib /usr/lib/x86_64-linux-gnu/libpthread.so)
endif (UNIX)

#ADD_EXECUTABLE(test main.cpp)

#TARGET_LINK_LIBRARIES(test Threadlib)
#TARGET_LINK_LIBRARIES(test pthread)
