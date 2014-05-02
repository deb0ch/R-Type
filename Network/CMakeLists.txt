SET(
  HEADER_FILES
  ISocketTCP.hh
  USocketTCP.hh
  WSocketTCP.hh
  ISocketUDP.hh
  WSocketUDP.hh
  USocketUDP.hh
  NetworkException.hh
  ISocket.hh
  Select.hh
  )

SET(
  SOURCES
  USocketTCP.cpp
  WSocketTCP.cpp
  USocketUDP.cpp
  WSocketUDP.cpp
  NetworkException.cpp
  Select.cpp
  )

SET (LIB_TYPE STATIC)

FILE(GLOB_RECURSE ${SOURCES} ${HEADER_FILES})

ADD_LIBRARY(Networklib ${LIB_TYPE} ${SOURCES})
