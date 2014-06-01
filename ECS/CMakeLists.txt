SET(HEADERS
  AComponent.hh
  AEvent.hh
  ASystem.hh
  Entity.hh
  IComponent.hh
  IEvent.hh
  ISystem.hh
  VectorDeleter.hpp
  World.hh
  Hash.hh
  ECSException.hh)

SET(SOURCES
  AEvent.cpp
  ASystem.cpp
  Entity.cpp
  World.cpp
  Hash.cpp
  ECSException.cpp)

SET(LIB_TYPE STATIC)

ADD_LIBRARY(ECSlib ${LIB_TYPE} ${HEADERS} ${SOURCES})
