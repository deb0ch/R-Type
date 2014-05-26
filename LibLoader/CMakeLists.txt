CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(LibLoader)

SET(HEADER_FILES
	ILibraryLoader.hh
	ULibraryLoader.hpp
	WLibraryLoader.hpp
	LibLoaderException.hh)

SET(SOURCES
	LibLoaderException.cpp
	main.cpp)

ADD_SUBDIRECTORY("test")

INCLUDE_DIRECTORIES(test)
	
ADD_EXECUTABLE(LibLoader ${SOURCES} ${HEADER_FILES})

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	INCLUDE_DIRECTORIES(/usr/include/)
	TARGET_LINK_LIBRARIES(LibLoader dl)
endif (UNIX)
