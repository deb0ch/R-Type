#include	<iostream>

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
#include	"EntitySpawnerSystem.hh"
#include	"ActionFireSystem.hh"
#include	"FireAlwaysSystem.hh"

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
#include	"EntitySpawnerComponent.hh"
#include	"FireAlwaysComponent.hh"

#include	"ImageLoader.hh"
#include	"ActionComponent.hh"

#include	"NetworkBuffer.hh"

#include	"ComponentFactory.hpp"
#include	"EntityFactory.hpp"
#include	"SoundLoader.hh"

#ifdef _WIN32
#define PATH "Ressources\\Images\\"
#elif __linux__
#define PATH "Ressources/Images/"
#endif

void		registerComponents(World &world)
{
	/*
	world.registerComponent(new Pos2DComponent());
	world.registerComponent(new SFMLSpriteComponent());
	world.registerComponent(new Speed2DComponent());
	world.registerComponent(new Friction2DComponent());
	*/
}

void		addSystems(World &world)
{
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

  CollisionSystem *collision;
  collision = new CollisionSystem();
  world.addSystem(collision);
  world.addEventHandler("CollisionEvent", collision, &LifeSystem::collision_event);

  EntityDeleterSystem *entityDeleterSystem;
  entityDeleterSystem = new EntityDeleterSystem();
  world.addSystem(entityDeleterSystem);
  world.addEventHandler("EntityDeletedEvent", entityDeleterSystem,
			&EntityDeleterSystem::addEntityToDelete);

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
  ComponentFactory *compos = new ComponentFactory();
  compos->init();
  EntityFactory *entityFactory = new EntityFactory();
  entityFactory->init();
  world.setSharedObject("imageLoader", new ImageLoader());
  world.setSharedObject("componentFactory", compos);
  world.setSharedObject("entityFactory", entityFactory);
}

void		addEntities(World &world)
{
  /*
  world.addEntity(world.createEntity()
		  ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		  ->addComponent(new Box2DComponent(50.0f, 50.0f))
		  ->addComponent(new Speed2DComponent(0.f, 0.f))
		  ->addComponent(new Friction2DComponent(0.5f))
		  ->addComponent(new SFMLSpriteComponent("players.png"))
		  ->addComponent(new SFMLInputComponent())
		  //->addComponent(new EntitySpawnerComponent({"TEST_BULLET"}))
		  //->addComponent(new CollisionPowerComponent(100))
		  ->addComponent(new MovementSpeedComponent(5))
		  ->addComponent((new ActionComponent())
				 ->addAction("UP")
				 ->addAction("RIGHT")
				 ->addAction("DOWN")
				 ->addAction("LEFT")
				 ->addAction("FIRE")
				 )
		  );

  world.addEntity(world.createEntity()
		  ->addComponent(new Pos2DComponent(100.0f, 150.0f))
		  ->addComponent(new Box2DComponent(50.0f, 50.0f))
		  ->addComponent(new Speed2DComponent(0.f, 0.f))
		  ->addComponent(new Friction2DComponent(0.5f))
		  ->addComponent(new SFMLSpriteComponent("players.png"))
		  ->addComponent(new SFMLInputComponent())
		  //->addComponent(new EntitySpawnerComponent({"TEST_BULLET"}))
		  //->addComponent(new CollisionPowerComponent(100))
		  ->addComponent(new MovementSpeedComponent(5))
		  ->addComponent((new ActionComponent())
				 ->addAction("UP")
				 ->addAction("RIGHT")
				 ->addAction("DOWN")
				 ->addAction("LEFT")
				 ->addAction("FIRE")
				 )
		  );

  world.addEntity(world.createEntity()
		  ->addComponent(new Pos2DComponent(600.0f, 200.0f))
		  ->addComponent(new Box2DComponent(10.0f, 10.0f))
		  ->addComponent(new Speed2DComponent(0.f, 0.f))
		  ->addComponent(new SFMLSpriteComponent(std::string("players.png")))
		  //->addComponent(new EntitySpawnerComponent({"TEST_SPAWN"}))
		  ->addComponent(new MovementSpeedComponent(0.5f))
		  ->addComponent(new MoveSequenceComponent(MoveSequenceComponent::UP_DOWN, 50))
		  ->addComponent(new Friction2DComponent(0.5f))
		  ->addComponent(new FireAlwaysComponent())
		  ->addComponent((new ActionComponent())
				 ->addAction("UP")
				 ->addAction("RIGHT")
				 ->addAction("DOWN")
				 ->addAction("LEFT")
				 ->addAction("FIRE")
				 )
		  );
  */
}


int		main()
{
  World		world;

  addSystems(world);
  addSharedObjetcs(world);
  addEntities(world);

	world.start();

	SoundLoader *s = new SoundLoader();
	s->addSound("Ressources/Sound/laser.wav");
	sf::Sound *sound = s->getSound("Ressources/Sound/laser.wav");
	sound->play();

	for (;;)
	{
	    world.process(0.16f);
	}
	world.stop();

  return (0);
}
