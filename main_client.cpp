
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

#include	"Timer.hh"

static float	g_fps = 60.f;

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
  EntityFactory *entityFactory = world.getSharedObject<EntityFactory>("entityFactory");
  if (entityFactory == NULL)
    return;
  world.addEntity(entityFactory->create("BACKGROUND_1"));
  world.addEntity(entityFactory->create("BACKGROUND_2"));
  world.addEntity(entityFactory->create("PLAYER_RED"));
  world.addEntity(entityFactory->create("BOSS_1"));
  world.addEntity(entityFactory->create("MONSTER_SPAWNER"));
}

int		main()
{
  World		world;
  Timer		timer;
  unsigned long	currentTime;
  unsigned long	previousTime;

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
  /*
    SoundLoader *s = new SoundLoader();
    s->addSound("Ressources/Sound/laser.wav");
    sf::Sound *sound = s->getSound("Ressources/Sound/laser.wav");
    sound->play();
  */
  previousTime = timer.getMilliTime();
  while (42)
    {
      currentTime = timer.getMilliTime();
      if (currentTime - previousTime >= 1000.0 / g_fps)
	{
	  std::cout << "delta = " << currentTime - previousTime << std::endl;
	  std::cout << "fps = " << 1000.f / (currentTime - previousTime) << std::endl;
	  world.process(currentTime - previousTime);
	  previousTime = currentTime;
	}
      else
	timer.milliSleep((1000.0 / g_fps) - (currentTime - previousTime));
    }
  world.stop();
  return (0);
}
