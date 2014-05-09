SET(HEADER_S
   ${HEADER_S}
	PARENT_SCOPE)

SET(SOURCE_S
	${SOURCE_S}
	PARENT_SCOPE)


SET(HEADER_C
   ${HEADER_C}
   	${CMAKE_CURRENT_SOURCE_DIR}/Speed2DComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLSpriteComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/Pos2DComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/Box2DComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/ISerializableComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/Friction2DComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLInputComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/PlayerMovementComponent.hh	
	${CMAKE_CURRENT_SOURCE_DIR}/MovementSpeedComponent.hh	
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkSendUpdateComponent.hh
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkReceiveUpdateComponent.hh
	PARENT_SCOPE
	)

SET(SOURCE_C
	${SOURCE_C}
	${CMAKE_CURRENT_SOURCE_DIR}/Speed2DComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLSpriteComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Pos2DComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Box2DComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Friction2DComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLInputComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MovementSpeedComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkSendUpdateComponent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkReceiveUpdateComponent.cpp
	PARENT_SCOPE
	)
