SET(
  HEADER_FILES
  AComponent.hh
  AEvent.hh
  ASystem.hh
  Entity.hh
  IComponent.hh
  IEvent.hh
  ISystem.hh
  VectorDeleter.hpp
  World.hh
  )

SET(
  SOURCES
  AComponent.cpp
  AEvent.cpp
  ASystem.cpp
  Entity.cpp
  World.cpp
  )

SET(LIB_TYPE STATIC)

# FILE(GLOB_RECURSE ${SOURCES} ${HEADER_FILES})

ADD_LIBRARY(ECSlib ${LIB_TYPE} ${SOURCES})
