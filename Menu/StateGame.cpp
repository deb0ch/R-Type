#include	"StateGame.hh"
#include	"Any.hpp"
#include	"AttachedToSystem.hh"

StateGame::StateGame(World *world)
{
  this->_world = world;
  this->addSystems();
  this->addSharedObjetcs();
  this->addEntities();
  this->_music = new sf::Music();
  if (this->_music->openFromFile("Ressources/Sound/music.ogg"))
    {
      this->_music->setLoop(true);
      this->_music->play();
    }
  this->_world->start();
}

StateGame::~StateGame()
{
  this->_world->stop();
  this->_music->stop();
  delete this->_music;
}

void		StateGame::addSharedObjetcs()
{
  SoundLoader *soundLoader = new SoundLoader();
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
	this->_world->addSystem(new AttachedToSystem());
	this->_world->addSystem(new SFMLInputSystem());
	this->_world->addSystem(new SFMLSoundSystem());
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
		"SFMLTextComponent",
		"AttachedToComponent",
		"SFMLJoystickComponent",
		"SFMLSoundComponent"
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

void		StateGame::update(StateManager &manager)
{
  if (!this->_world->isRunning())
    manager.exit();
}

void		StateGame::render(const Timer&timer)
{
  this->_world->process(timer.getDeltaTime());
}
