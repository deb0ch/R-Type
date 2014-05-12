CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(LibLoader)

SET(HEADER_FILES
	ILibraryLoader.hh
	ULibraryLoader.hpp
	WLibraryLoader.hpp
	LibLoaderException.hh)

SET(SOURCES
	#main.cpp
	LibLoaderException.cpp)
      
SET (LIB_TYPE STATIC)

ADD_LIBRARY(LibLoader ${LIB_TYPE} ${SOURCES} ${HEADER_FILES})

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	INCLUDE_DIRECTORIES(/usr/include/)
	TARGET_LINK_LIBRARIES(LibLoader /usr/lib/x86_64-linux-gnu/libdl.so)
endif (UNIX)
