CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project (R-Type)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
set(EXECUTABLE_SOURCE_DIR, {CMAKE_SOURCE_DIR})
set(HEADER_FILES 
	ISocketTCP.hh
	USocketTCP.hh
	WSocketTCP.
	ISocketUDP.hh
	WSocketUDP.hh
	USocketUDP.hh
	NetworkException.hh
	ISocket.hh)
	
set(SOURCES USocketTCP.cpp
	WSocketTCP.cpp
	USocketUDP.cpp
	WSocketUDP.cpp
	NetworkException.cpp
	main.cpp)

file(GLOB_RECURSE ${SOURCES} ${HEADER_FILES})

add_executable(R-Type ${SOURCES})