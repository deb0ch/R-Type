#ifndef STATESOLOGAME_H_
# define STATESOLOGAME_H_

#include	"SFML/Audio/Music.hpp"

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSoloSystem.hh"
#include	"SFMLRenderSystem.hh"
#include	"SFMLDisplaySystem.hh"
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
#include	"SpawnPlayerSystem.hh"
#include	"NetworkSendDieEntitySystem.hh"
#include	"DisconnectPlayerSystem.hh"
#include	"PowerUpSystem.hh"
#include	"PlayerLifeSystem.hh"
#include	"SFMLRenderTextSystem.hh"
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

#include	"ImageLoader.hh"
#include	"ActionComponent.hh"

#include	"NetworkBuffer.hh"

#include	"ComponentFactory.hpp"
#include	"EntityFactory.hpp"
#include	"SoundLoader.hh"

#include	"ServerRelay.hh"
#include	"Threads.hh"

#include	"Timer.hh"

#include	"IState.hh"
#include	"StateManager.hh"
#include	"SpawnSoloPlayerSystem.hh"

class StateSoloGame : public IState
{
public:
	StateSoloGame(World *world);
	~StateSoloGame();

	void update(StateManager&);
	void render(const Timer&);

protected:
	void addSharedObjetcs();
	void addEntities();
	void addSystems();
	void createConfigFile() const;


	World		*_world;
	sf::Music	*_music;
};

#endif /* !STATESOLOGAME_H_ */
