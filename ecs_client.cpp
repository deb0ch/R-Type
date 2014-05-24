#include	<iostream>

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"
#include	"SFMLInputSystem.hh"
#include	"EntityDeleterSystem.hh"
#include	"OutOfBoundsSystem.hh"
#include	"NetworkSendUpdateSystem.hh"
#include	"NetworkReceiveUpdateSystem.hh"
#include	"SFMLEventSystem.hh"
#include	"MoveFollowSystem.hh"
#include	"NetworkSendActionSystem.hh"

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

#include	"ImageLoader.hh"
#include	"ActionComponent.hh"

#include	"NetworkBuffer.hh"

#include	"ComponentFactory.hpp"

#include	"ClientRelay.hh"

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
	// world.addSystem(new OutOfBoundsSystem());
	// world.addSystem(new MoveFollowSystem());
	world.addSystem(new PlayerMovementSystem());

	// CollisionSystem *collision;
	// collision = new CollisionSystem();
	// world.addSystem(collision);
	// world.addEventHandler("CollisionEvent", collision, &CollisionSystem::collision_event);

	// EntityDeleterSystem *entityDeleterSystem;
	// entityDeleterSystem = new EntityDeleterSystem();
	// world.addSystem(entityDeleterSystem);
	// world.addEventHandler("EntityDeletedEvent", entityDeleterSystem,
	// 	&EntityDeleterSystem::addEntityToDelete);
	std::vector<std::string> arg =
	  { "Pos2DComponent",
	    "SFMLSpriteComponent",
	    "Speed2DComponent",
	    "Friction2DComponent",
	    "ActionComponent",
	    "PlayerMovementComponent",
	    "MovementSpeedComponent",
	    "NetworkSendActionComponent",
	    "SFMLInputComponent" };
	world.addSystem(new NetworkReceiveUpdateSystem(arg));
	std::vector<std::string> serializable_action =
	  { "UP",
	    "RIGHT",
	    "DOWN",
	    "LEFT",
	    "FIRE" };
	world.addSystem(new NetworkSendActionSystem(serializable_action));
}

static std::string g_ip = "127.0.0.1";

void		addSharedObjetcs(World &world)
{
	ComponentFactory	*compos = new ComponentFactory();
	ClientRelay *client = new ClientRelay(g_ip, 6667);
	Thread<ClientRelay> *thread = new Thread<ClientRelay>();
	Any tmp;

	thread->start(client, &ClientRelay::start, tmp);
	compos->init();
	world.setSharedObject("imageLoader", new ImageLoader());
	world.setSharedObject("componentFactory", compos);
	world.setSharedObject("NetworkRelay", static_cast<INetworkRelay *>(client));
	world.setSharedObject("RoomName", new std::string("default"));
}

void		addEntities(World &world)
{

	ComponentFactory *test = world.getSharedObject<ComponentFactory>("componentFactory");

	delete test->create(Hash()("Pos2DComponent"));
	delete test->create(Hash()("Box2DComponent"));
	delete test->create(Hash()("Speed2DComponent"));
	delete test->create(Hash()("Friction2DComponent"));
	delete test->create(Hash()("SFMLInputComponent"));
	delete test->create(Hash()("MovementSpeedComponent"));
	delete test->create(Hash()("ActionComponent"));

	// world.addEntity(world.createEntity()
	// 	->addComponent(new Pos2DComponent(0.0f, 100.0f))
	// 	->addComponent(new Speed2DComponent(5.f, 5.f))
	// 	->addComponent(new Friction2DComponent(0.1f))
	// 	->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png")))
	// 	->addComponent(new SFMLInputComponent())
	// 	->addComponent(new MovementSpeedComponent(1))
	// 	->addComponent(new PlayerMovementComponent())
	// 	->addComponent((new ActionComponent())
	// 	->addAction("UP")
	// 	->addAction("RIGHT")
	// 	->addAction("DOWN")
	// 	->addAction("LEFT")
	// 	)
	// 	);
	// world.addEntity(world.createEntity()
	// 	->addComponent(test->create(Hash()("Pos2DComponent"))->clone())
	// 	->addComponent(test->create(Hash()("Box2DComponent"))->clone())
	// 	->addComponent(test->create(Hash()("Speed2DComponent"))->clone())
	// 	->addComponent(test->create(Hash()("Friction2DComponent"))->clone())
	// 	->addComponent(test->create(Hash()("SFMLInputComponent"))->clone())
	// 	->addComponent(test->create(Hash()("MovementSpeedComponent"))->clone())
	// 	->addComponent(test->create(Hash()("ActionComponent"))->clone())
	// 	->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png")))
	// 	);

	// world.addEntity(world.createEntity()
	// 	->addComponent(new Pos2DComponent(100.0f, 200.0f))
	// 	->addComponent(new Box2DComponent(10.0f, 10.0f))
	// 	->addComponent(new Speed2DComponent(5.f, 2.f))
	// 	->addComponent(new Friction2DComponent(0.9f))
	// 	->addComponent(new MovementSpeedComponent(0.8f))
	// 	->addComponent(new PlayerMovementComponent())
	// 	->addComponent(new MoveFollowComponent(world.getEntity(1)))
	// 	->addComponent((new ActionComponent())
	// 	->addAction("UP")
	// 	->addAction("RIGHT")
	// 	->addAction("DOWN")
	// 	->addAction("LEFT")
	// 	)
	// 	->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png"))));

	// world.addEntity(world.createEntity()
	// 	->addComponent(new Pos2DComponent(800.0f, 000.0f))
	// 	->addComponent(new Box2DComponent(10.0f, 10.0f))
	// 	->addComponent(new Speed2DComponent(-4.f, 5.f))
	// 	->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png"))));

	// world.addEntity(world.createEntity()
	// 	->addComponent(new Pos2DComponent(300.0f, 000.0f))
	// 	->addComponent(new Box2DComponent(10.0f, 10.0f))
	// 	->addComponent(new Speed2DComponent(20.f, 5.f))
	// 	->addComponent(new SFMLSpriteComponent(PATH + std::string("players.png"))));
}

int			main(int ac, char **av)
{
	World		world;

	if (ac >= 2)
	  {
	    g_ip = av[1];
	  }
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