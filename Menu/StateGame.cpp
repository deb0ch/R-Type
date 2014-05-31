#include	"SFMLDisplaySystem.hh"
#include	"SFMLRenderTextSystem.hh"
#include	"StateGame.hh"
#include	"Any.hpp"

StateGame::StateGame(World *world)
{
  this->_world = world;
  this->addSystems();
  this->addSharedObjetcs();
  this->addEntities();

  /*
    sf::Music music;

    if (music.openFromFile("Ressources/Sound/music.ogg"))
    {
    music.setLoop(true);
    music.play();
    }
  */

  sf::Music *music = new sf::Music();

  if (music->openFromFile("Ressources/Sound/music.ogg"))
    {
      music->setLoop(true);
      music->play();
    }

  this->_world->start();
}

StateGame::~StateGame()
{
  this->_world->stop();
}

void		StateGame::addSharedObjetcs()
{
  SoundLoader *soundLoader = new SoundLoader();
  soundLoader->addSound("Ressources/Sound/Silencer.wav");

  ComponentFactory *compos = new ComponentFactory();
  EntityFactory *entityFactory = new EntityFactory();

  compos->init();
  entityFactory->init();
  this->_world->setSharedObject("imageLoader", new ImageLoader());
  this->_world->setSharedObject("componentFactory", compos);
  this->_world->setSharedObject("entityFactory", entityFactory);
  this->_world->setSharedObject("soundLoader", soundLoader);
  this->_world->setSharedObject("RoomName", new std::string("default"));
}

void		StateGame::addEntities()
{
  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");

  if (entityFactory == NULL)
    return;
  this->_world->addEntity(entityFactory->create("BACKGROUND_1"));
  this->_world->addEntity(entityFactory->create("BACKGROUND_2"));
}

void		StateGame::addSystems()
{
	this->_world->addSystem(new SFMLEventSystem());
	this->_world->addSystem(new SFMLInputSystem());
	this->_world->addSystem(new SFMLDisplaySystem());
	this->_world->addSystem(new SFMLRenderSystem());
	this->_world->addSystem(new SFMLRenderTextSystem());
	this->_world->addSystem(new MoveFollowSystem());
	this->_world->addSystem(new MoveForwardSystem());
	this->_world->addSystem(new MoveSequenceSystem());
	this->_world->addSystem(new ActionMovementSystem());
	this->_world->addSystem(new SyncPos2DSystem());
	this->_world->addSystem(new ActionFireSystem());
	this->_world->addSystem(new Friction2DSystem());
	this->_world->addSystem(new MoveSystem());
	this->_world->addSystem(new ResetActionSystem());
	this->_world->addSystem(new MovementLimitFrame2DSystem());
	this->_world->addSystem(new BackgroundSystem());
	this->_world->addSystem(new NetworkReceiveDieEntitySystem());
	this->_world->addSystem(new NetworkTimeOutEntitySystem());
	this->_world->addSystem(new SFMLSetDisplayLiveSystem());

	CollisionSystem *collision;

	collision = new CollisionSystem();
	this->_world->addSystem(collision);
	this->_world->addEventHandler("CollisionEvent", collision, &LifeSystem::collision_event);

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
		"MovementSpeedComponent",
		"MoveForwardComponent",
		"MoveFollowComponent",
		"MoveSequenceComponent",
		"TagComponent",
		"SyncPos2DComponent",
		"MovementLimitFrame2DComponent",
		"SFMLTextComponent"
		"SFMLJoystickComponent"
	};

	this->_world->addSystem(new NetworkReceiveUpdateSystem(arg));

	std::vector<std::string> serializable_action =
	{
		"UP",
		"RIGHT",
		"DOWN",
		"LEFT",
		"FIRE"
	};

	this->_world->addSystem(new NetworkSendActionSystem(serializable_action));

	EntityDeleterSystem *entityDeleterSystem = new EntityDeleterSystem();
	this->_world->addSystem(entityDeleterSystem);
	this->_world->addEventHandler("EntityDeletedEvent", entityDeleterSystem,
		&EntityDeleterSystem::addEntityToDelete);
}

void		StateGame::update(StateManager&)
{}

void		StateGame::render(const Timer&timer)
{
	this->_world->process(timer.getDeltaTime() / 1000000.f);
}
