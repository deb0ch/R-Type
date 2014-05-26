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
#include	"NetworkSendActionSystem.hh"
#include	"NetworkReceiveActionSystem.hh"
#include	"NetworkReceiveDieEntitySystem.hh"
#include	"SyncPos2DSystem.hh"
#include	"NetworkTimeOutEntitySystem.hh"

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

#include	"ClientRelay.hh"
#include	"Threads.hh"

#include	"Timer.hh"

void		addSystems(World &world)
{
  world.addSystem(new SFMLEventSystem());
  world.addSystem(new SFMLInputSystem());
  world.addSystem(new SFMLRenderSystem());
  world.addSystem(new ActionMovementSystem());
  world.addSystem(new ActionFireSystem());
  // world.addSystem(new SyncPos2DSystem());
  world.addSystem(new Friction2DSystem());
  world.addSystem(new MoveSystem());
  world.addSystem(new ResetActionSystem());
  world.addSystem(new MovementLimitFrame2DSystem());
  world.addSystem(new BackgroundSystem());
  world.addSystem(new NetworkReceiveDieEntitySystem());
  world.addSystem(new NetworkTimeOutEntitySystem());

  CollisionSystem *collision;

  collision = new CollisionSystem();
  world.addSystem(collision);
  world.addEventHandler("CollisionEvent", collision, &LifeSystem::collision_event);

  std::vector<std::string> arg =
    {
      "Pos2DComponent",
      "SFMLSpriteComponent",
      "Speed2DComponent",
      "Friction2DComponent",
      "ActionComponent",
      "MovementSpeedComponent",
      "NetworkSendActionComponent",
      "SFMLInputComponent",
      "Box2DComponent",
      "SyncPos2DComponent"
    };

  world.addSystem(new NetworkReceiveUpdateSystem(arg));

  std::vector<std::string> serializable_action =
    {
      "UP",
      "RIGHT",
      "DOWN",
      "LEFT",
      "FIRE"
    };

  world.addSystem(new NetworkSendActionSystem(serializable_action));

  EntityDeleterSystem *entityDeleterSystem = new EntityDeleterSystem();
  world.addSystem(entityDeleterSystem);
  world.addEventHandler("EntityDeletedEvent", entityDeleterSystem,
			&EntityDeleterSystem::addEntityToDelete);
}

static std::string g_ip = "127.0.0.1";

void		addSharedObjetcs(World &world)
{
	SoundLoader *soundLoader = new SoundLoader();
	soundLoader->addSound("Ressources/Sound/Silencer.wav");
	/*

	*/

  ComponentFactory *compos = new ComponentFactory();
  ClientRelay *client = new ClientRelay(g_ip, 6667);
  EntityFactory *entityFactory = new EntityFactory();
  Thread<ClientRelay> *thread = new Thread<ClientRelay>();
  Any tmp;

  thread->start(client, &ClientRelay::start, tmp);
  compos->init();
  entityFactory->init();
  world.setSharedObject("imageLoader", new ImageLoader());
  world.setSharedObject("componentFactory", compos);
  world.setSharedObject("entityFactory", entityFactory);
  world.setSharedObject("soundLoader", soundLoader);
  world.setSharedObject("NetworkRelay", static_cast<INetworkRelay *>(client));
  world.setSharedObject("RoomName", new std::string("default"));
}

void		addEntities(World &world)
{
  EntityFactory *entityFactory = world.getSharedObject<EntityFactory>("entityFactory");

  if (entityFactory == NULL)
    return;
  world.addEntity(entityFactory->create("BACKGROUND_1"));
  world.addEntity(entityFactory->create("BACKGROUND_2"));
}

int		main(int ac, char **av)
{
  World		world;
  Timer		timer;

  try {
    if (ac >= 2)
      g_ip = av[1]; // Master flemme
    addSystems(world);
    addSharedObjetcs(world);
    addEntities(world);

    sf::Music music;

    if (music.openFromFile("Ressources/Sound/music.ogg"))
      {
	music.setLoop(true);
	music.play();
      }
    /*
      SoundLoader *s = new SoundLoader();
      s->addSound("Ressources/Sound/laser.wav");
      sf::Sound *sound = s->getSound("Ressources/Sound/laser.wav");
      sound->play();
    */
    world.start();
    while (42)
      {
	timer.startFrame();
	if (timer.canTick())
	  {
	    //std::cout << "fps = " << timer.getCurrentFps() << std::endl;
	    world.process(timer.getDeltaTime() / 1000000.f);
	  }
	timer.endFrame();
      }
    world.stop();
  } catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  return (0);
}
