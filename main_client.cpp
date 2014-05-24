#include	<iostream>

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

void		addSystems(World &world)
{
  world.addSystem(new AutoDestructSystem());
  world.addSystem(new EntitySpawnerSystem());
  world.addSystem(new SFMLEventSystem());
  world.addSystem(new SFMLInputSystem());
  world.addSystem(new SFMLRenderSystem());
  world.addSystem(new OutOfBoundsSystem());
  world.addSystem(new MoveFollowSystem());
  world.addSystem(new MoveForwardSystem());
  world.addSystem(new MoveSequenceSystem());
  world.addSystem(new FireAlwaysSystem());
  world.addSystem(new ActionMovementSystem());
  world.addSystem(new ActionFireSystem());
  world.addSystem(new Friction2DSystem());
  world.addSystem(new MoveSystem());
  world.addSystem(new LifeSystem());
  world.addSystem(new ResetActionSystem());
  world.addSystem(new MovementLimitFrame2DSystem());
  world.addSystem(new BackgroundSystem());

  CollisionSystem *collision;
  collision = new CollisionSystem();
  world.addSystem(collision);
  world.addEventHandler("CollisionEvent", collision, &LifeSystem::collision_event);

  EntityDeleterSystem *entityDeleterSystem;
  entityDeleterSystem = new EntityDeleterSystem();
  world.addSystem(entityDeleterSystem);
  world.addEventHandler("EntityDeletedEvent", entityDeleterSystem,
			&EntityDeleterSystem::addEntityToDelete);
  world.addEventHandler("EntityDeletedEvent", entityDeleterSystem,
	  &LifeSystem::delete_entity);

  /*
  NetworkSendUpdateSystem *network;
  std::vector<std::string> arg =
    { "Pos2DComponent",
      "SFMLSpriteComponent",
      "Speed2DComponent",
      "Friction2DComponent" };
  network = new NetworkSendUpdateSystem(arg);
  */
  //world.addSystem(network);
  //world.addSystem(new NetworkReceiveUpdateSystem());
}

void		addSharedObjetcs(World &world)
{
	SoundLoader *soundLoader = new SoundLoader();
	soundLoader->addSound("Ressources/Sound/Silencer.wav");
	/*

	*/

  ComponentFactory *compos = new ComponentFactory();
  compos->init();
  EntityFactory *entityFactory = new EntityFactory();
  entityFactory->init();
  world.setSharedObject("imageLoader", new ImageLoader());
  world.setSharedObject("componentFactory", compos);
  world.setSharedObject("entityFactory", entityFactory);
  world.setSharedObject("soundLoader", soundLoader);
}

void		addEntities(World &world)
{
	EntityFactory *entityFactory = world.getSharedObject<EntityFactory>("entityFactory");
	if (entityFactory == NULL)
		return;
	world.addEntity(entityFactory->create("BACKGROUND_1"));
	world.addEntity(entityFactory->create("BACKGROUND_2"));
	world.addEntity(entityFactory->create("PLAYER_RED"));
	//world.addEntity(entityFactory->create("BOSS_1"));
	world.addEntity(entityFactory->create("MONSTER_SPAWNER"));
}

int		main()
{
  World		world;

  addSystems(world);
  addSharedObjetcs(world);
  addEntities(world);

	world.start();

	sf::Music music;
	
	if (music.openFromFile("Ressources/Sound/music.ogg"))
	{
	  music.setLoop(true);
	  music.play();
	}

	for (;;)
	{
	    world.process(0.16f);
	}
	world.stop();

  return (0);
}
