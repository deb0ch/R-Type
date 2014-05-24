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

void		addSystems(World &world)
{
  world.addSystem(new SFMLEventSystem());
  world.addSystem(new SFMLInputSystem());
  world.addSystem(new SFMLRenderSystem());
  world.addSystem(new ActionMovementSystem());
  world.addSystem(new ActionFireSystem());
  world.addSystem(new Friction2DSystem());
  world.addSystem(new MoveSystem());
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

  std::vector<std::string> arg =
    { "Pos2DComponent",
      "SFMLSpriteComponent",
      "Speed2DComponent",
      "Friction2DComponent",
      "ActionComponent",
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

void		addSharedObjetcs(World &world)
{
  ComponentFactory *compos = new ComponentFactory();
  EntityFactory *entityFactory = new EntityFactory();

  compos->init();
  entityFactory->init();
  world.setSharedObject("imageLoader", new ImageLoader());
  world.setSharedObject("componentFactory", compos);
  world.setSharedObject("entityFactory", entityFactory);
}

// void		addEntities(World &world)
// {
//   EntityFactory *entityFactory = world.getSharedObject<EntityFactory>("entityFactory");

//   if (entityFactory == NULL)
//     return;
//   world.addEntity(entityFactory->create("BACKGROUND_1"));
//   world.addEntity(entityFactory->create("BACKGROUND_2"));
//   world.addEntity(entityFactory->create("PLAYER_RED"));
//   world.addEntity(entityFactory->create("BOSS_1"));
//   world.addEntity(entityFactory->create("MONSTER_SPAWNER"));
// }

int		main()
{
  World		world;
  Timer		timer;

  addSystems(world);
  addSharedObjetcs(world);
  // addEntities(world);

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
	world.process(timer.getDeltaTime() / 1000000.f);
      timer.endFrame();
    }
  world.stop();
  return (0);
}
