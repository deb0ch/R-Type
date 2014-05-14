set(HEADER_S
   ${HEADER_S}
	PARENT_SCOPE)

SET(SOURCE_S
	${SOURCE_S}
	PARENT_SCOPE)



set(HEADER_C
	${HEADER_C}
	${CMAKE_CURRENT_SOURCE_DIR}/CollisionSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/MoveSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkSendUpdateSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkReceiveUpdateSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLRenderSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/Friction2DSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLInputSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/ActionMovementSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/EntityDeleterSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/OutOfBoundsSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLEventSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/MoveFollowSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/MoveForwardSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/MoveSequenceSystem.hh
	${CMAKE_CURRENT_SOURCE_DIR}/ResetActionSystem.hh
	PARENT_SCOPE
)

SET(SOURCE_C
	${SOURCE_C}
	${CMAKE_CURRENT_SOURCE_DIR}/CollisionSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MoveSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkSendUpdateSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/NetworkReceiveUpdateSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLRenderSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Friction2DSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLInputSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ActionMovementSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EntityDeleterSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/OutOfBoundsSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SFMLEventSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MoveFollowSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MoveForwardSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MoveSequenceSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ResetActionSystem.cpp
	PARENT_SCOPE
)
