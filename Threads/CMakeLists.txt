CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

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
  SafeFifo.hpp
  ICondVar.hh
  UCondVar.hh
  WCondVar.hh
  LockGuard.hpp
  SafeFifoException.hh)

SET(SOURCES
  ThreadException.cpp
  MutexException.cpp
  UMutex.cpp
  WMutex.cpp
  ScopedMutex.cpp
  UCondVar.cpp
  WCondVar.cpp
  SafeFifoException.cpp
  )

SET (LIB_TYPE STATIC)
	
ADD_LIBRARY(Threadlib ${LIB_TYPE} ${HEADERS} ${SOURCES})
#ADD_EXECUTABLE(Threadlib ${HEADERS} ${SOURCES})

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb3 -O0 -Wall -Wextra")
	INCLUDE_DIRECTORIES(/usr/include/)
	TARGET_LINK_LIBRARIES(Threadlib -pthread)
endif (UNIX)
