#ifndef STATEGAME_H_
# define STATEGAME_H_

#include	"SFML/Audio/Music.hpp"

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"
#include	"SFMLInputSystem.hh"
#include	"ActionMovementSystem.hh"
#include	"EntityDeleterSystem.hh"
#include	"OutOfBoundsSystem.hh"
#include	"NetworkSendUpdateSystem.hh"
#include	"NetworkReceiveUpdateSystem.hh"
#include	"SFMLEventSystem.hh"
#include	"MoveFollowSystem.hh"
#include	"MoveForwardSystem.hh"
#include	"MoveSequenceSystem.hh"
#include	"ResetActionSystem.hh"
#include	"LifeSystem.hh"
#include	"BackgroundSystem.hh"
#include	"EntitySpawnerSystem.hh"
#include	"ActionFireSystem.hh"
#include	"FireAlwaysSystem.hh"
#include	"MovementLimitFrame2DSystem.hh"
#include	"AutoDestructSystem.hh"
#include	"NetworkSendActionSystem.hh"
#include	"NetworkReceiveActionSystem.hh"
#include	"NetworkReceiveDieEntitySystem.hh"
#include	"SyncPos2DSystem.hh"
#include	"NetworkTimeOutEntitySystem.hh"
#include	"SFMLSetDisplayLiveSystem.hh"

#include	"CollisionComponent.hh"
#include	"Pos2DComponent.hh"
#include	"Speed2DComponent.hh"
#include	"Friction2DComponent.hh"
#include	"Box2DComponent.hh"
#include	"SFMLSpriteComponent.hh"
#include	"SFMLInputComponent.hh"
#include	"MovementSpeedComponent.hh"
#include	"NetworkSendUpdateComponent.hh"
#include	"NetworkReceiveUpdateComponent.hh"
#include	"MoveFollowComponent.hh"
#include	"MoveForwardComponent.hh"
#include	"MoveSequenceComponent.hh"
#include	"MoveSequenceComponent.hh"
#include	"LifeComponent.hh"
#include	"CollisionPowerComponent.hh"
#include	"TagComponent.hh"
#include	"EntitySpawnerComponent.hh"
#include	"FireAlwaysComponent.hh"
#include	"MovementLimitFrame2DComponent.hh"
#include	"ActionComponent.hh"

#include	"ImageLoader.hh"
#include	"ClientRelay.hh"
#include	"Threads.hh"
#include	"NetworkBuffer.hh"
#include	"ComponentFactory.hpp"
#include	"EntityFactory.hpp"
#include	"SoundLoader.hh"
#include	"StateManager.hh"
#include	"Timer.hh"

class StateGame : public IState
{
public:
	StateGame(World *world);
	~StateGame();

	void update(StateManager&);
	void render(const Timer&);

protected:
	void addSharedObjetcs();
	void addEntities();
	void addSystems();


	World		*_world;
	sf::Music	*_music;
};

#endif /* !STATEGAME_H_ */
