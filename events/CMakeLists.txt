set(HEADER
  ${HEADER}
  ${CMAKE_CURRENT_SOURCE_DIR}/CollisionEvent.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/EntityDeletedEvent.hh
  PARENT_SCOPE
  )

SET(SOURCE
  ${SOURCE}
  ${CMAKE_CURRENT_SOURCE_DIR}/CollisionEvent.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/EntityDeletedEvent.cpp
  PARENT_SCOPE
  )