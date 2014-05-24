CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(HEADER_FILES
  ISocketTCP.hh
  USocketTCP.hh
  WSocketTCP.hh
  ISocketUDP.hh
  WSocketUDP.hh
  USocketUDP.hh
  NetworkException.hh
  TCPException.hh
  UDPException.hh
  SelectException.hh
  ISocket.hh
  Select.hh
  IBuffer.hh
  NetworkBuffer.hh
  NetworkInitializer.hh)

SET(SOURCES
  USocketTCP.cpp
  WSocketTCP.cpp
  USocketUDP.cpp
  WSocketUDP.cpp
  NetworkException.cpp
  TCPException.cpp
  UDPException.cpp
  SelectException.cpp
  Select.cpp
  NetworkBuffer.cpp
  WNetworkInitializer.cpp
  UNetworkInitializer.cpp)

SET (LIB_TYPE STATIC)

FILE(GLOB_RECURSE ${SOURCES} ${HEADER_FILES})

ADD_LIBRARY(Networklib ${LIB_TYPE} ${SOURCES})

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra -Werror")
endif (UNIX)
