#include	<iostream>

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"
#include	"SFMLInputSystem.hh"
#include	"PlayerMovementSystem.hh"
#include	"EntityDeleterSystem.hh"
#include	"OutOfBoundsSystem.hh"
#include	"NetworkSendUpdateSystem.hh"
#include	"NetworkReceiveUpdateSystem.hh"
#include	"SFMLEventSystem.hh"
#include	"MoveFollowSystem.hh"
#include	"NetworkReceiveActionSystem.hh"

#include	"Pos2DComponent.hh"
#include	"Speed2DComponent.hh"
#include	"Friction2DComponent.hh"
#include	"Box2DComponent.hh"
#include	"SFMLSpriteComponent.hh"
#include	"SFMLInputComponent.hh"
#include	"PlayerMovementComponent.hh"
#include	"MovementSpeedComponent.hh"
#include	"NetworkSendUpdateComponent.hh"
#include	"NetworkReceiveUpdateComponent.hh"
#include	"MoveFollowComponent.hh"

#include	"ImageLoader.hh"
#include	"ActionComponent.hh"

#include	"NetworkBuffer.hh"

#include	"ComponentFactory.hpp"

#include	"ServerRelay.hh"

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
	world.addSystem(new MoveSystem());
	world.addSystem(new Friction2DSystem());
	world.addSystem(new SFMLRenderSystem());
	world.addSystem(new SFMLEventSystem());
	world.addSystem(new SFMLInputSystem());
	world.addSystem(new OutOfBoundsSystem());
	world.addSystem(new MoveFollowSystem());
	world.addSystem(new PlayerMovementSystem());

	CollisionSystem *collision;
	collision = new CollisionSystem();
	world.addSystem(collision);
	world.addEventHandler("CollisionEvent", collision, &CollisionSystem::collision_event);

	EntityDeleterSystem *entityDeleterSystem;
	entityDeleterSystem = new EntityDeleterSystem();
	world.addSystem(entityDeleterSystem);
	world.addEventHandler("EntityDeletedEvent", entityDeleterSystem,
		&EntityDeleterSystem::addEntityToDelete);

	NetworkSendUpdateSystem *network;
	std::vector<std::string> arg =
	  { "Pos2DComponent",
	    "SFMLSpriteComponent",
	    "Speed2DComponent",
	    "Friction2DComponent",
	    "ActionComponent",
	    "PlayerMovementComponent",
	    "PlayerMovementComponent",
	    "NetworkSendActionComponent",
	    "SFMLInputComponent" };
	network = new NetworkSendUpdateSystem(arg);
	world.addSystem(network);
	// world.addSystem(new NetworkReceiveUpdateSystem());
	std::vector<std::string> serializable_action =
	  { "UP",
	    "RIGHT",
	    "DOWN",
	    "LEFT",
	    "FIRE" };
	world.addSystem(new NetworkReceiveActionSystem(serializable_action));
}

void		addSharedObjetcs(World &world)
{
	ComponentFactory *compos = new ComponentFactory();
	ServerRelay *server = new ServerRelay(6667, 42);
	Thread<ServerRelay> *thread = new Thread<ServerRelay>();
	Any tmp;

	world.setSharedObject("NetworkRelay", static_cast<INetworkRelay *>(server));
	world.setSharedObject("RoomName", new std::string("default"));
	thread->start(server, &ServerRelay::start, tmp);
	compos->init();
	world.setSharedObject("imageLoader", new ImageLoader());
	world.setSharedObject("componentFactory", compos);
}

void		addEntities(World &world)
{
  Entity *tmp;
  ComponentFactory *test = world.getSharedObject<ComponentFactory>("componentFactory");

	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(0.0f, 100.0f))
		->addComponent(new Speed2DComponent(5.f, 5.f))
		->addComponent(new Friction2DComponent(0.5f))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png")))
		->addComponent(new SFMLInputComponent())
		->addComponent(new MovementSpeedComponent(1))
		->addComponent(new PlayerMovementComponent())
		->addComponent(new NetworkSendUpdateComponent())
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("RIGHT")
		->addAction("DOWN")
		->addAction("LEFT")
		)
		);

	tmp = world.createEntity()
	  ->addComponent(test->create(Hash()("Pos2DComponent"))->clone())
	  ->addComponent(test->create(Hash()("Box2DComponent"))->clone())
	  ->addComponent(test->create(Hash()("Speed2DComponent"))->clone())
	  ->addComponent(test->create(Hash()("Friction2DComponent"))->clone())
	  ->addComponent(test->create(Hash()("SFMLInputComponent"))->clone())
	  ->addComponent(test->create(Hash()("MovementSpeedComponent"))->clone())
	  ->addComponent(test->create(Hash()("ActionComponent"))->clone())
	  ->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png")))
	  ->addComponent(new NetworkSendUpdateComponent())
	  ->addComponent(new NetworkReceiveActionComponent());
	tmp->addComponent(new NetworkSendActionComponent(tmp->_id)); // change this to TAG latter?
	world.addEntity(tmp);

	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(100.0f, 200.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(5.f, 2.f))
		->addComponent(new Friction2DComponent(0.9f))
		->addComponent(new MovementSpeedComponent(0.8f))
		->addComponent(new PlayerMovementComponent())
		->addComponent(new MoveFollowComponent(world.getEntity(1)))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png")))
		->addComponent(new NetworkSendUpdateComponent())
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("RIGHT")
		->addAction("DOWN")
		->addAction("LEFT")
			       ));

	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(800.0f, 000.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(-4.f, 5.f))
		->addComponent(new NetworkSendUpdateComponent())
		->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png"))));

	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(300.0f, 000.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(20.f, 5.f))
		->addComponent(new NetworkSendUpdateComponent())
		->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png"))));
}

int			main()
{
	World		world;

	registerComponents(world);
	addSystems(world);
	addSharedObjetcs(world);
	addEntities(world);

	world.start();
	for (;;)
	{
		world.process(0.16f);
	}
	world.stop();

	return (0);
}
