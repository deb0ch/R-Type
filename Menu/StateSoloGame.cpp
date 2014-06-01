#include	"StateSoloGame.hh"
#include	"AttachSystem.hh"
#include	"AttachedToSystem.hh"

StateSoloGame::StateSoloGame(World *world)
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

StateSoloGame::~StateSoloGame()
{
	this->_world->stop();
	this->_music->stop();
	delete this->_music;
}

void		StateSoloGame::addSystems()
{
	this->_world->addSystem(new AutoDestructSystem());
	this->_world->addSystem(new AttachSystem());
	this->_world->addSystem(new AttachedToSystem());
	this->_world->addSystem(new EntitySpawnerSystem());
	this->_world->addSystem(new SFMLEventSystem());
	this->_world->addSystem(new SFMLInputSystem());
	this->_world->addSystem(new SFMLDisplaySystem());
	this->_world->addSystem(new SFMLRenderSystem());
	this->_world->addSystem(new SFMLRenderTextSystem());
	this->_world->addSystem(new OutOfBoundsSystem());
	this->_world->addSystem(new MoveFollowSystem());
	this->_world->addSystem(new MoveForwardSystem());
	this->_world->addSystem(new MoveSequenceSystem());
	this->_world->addSystem(new FireAlwaysSystem());
	this->_world->addSystem(new ActionMovementSystem());
	this->_world->addSystem(new ActionFireSystem());
	this->_world->addSystem(new Friction2DSystem());
	this->_world->addSystem(new MoveSystem());
	this->_world->addSystem(new LifeSystem());
	this->_world->addSystem(new ResetActionSystem());
	this->_world->addSystem(new MovementLimitFrame2DSystem());
	this->_world->addSystem(new SpawnSoloPlayerSystem("PLAYER_RED"));
	this->_world->addSystem(new BackgroundSystem());
	std::vector<std::string> power_ups =
	  {"POWERUP_1", "POWERUP_2", "POWERUP_3", "POWERUP_LIFE", "POWERUP_FORCE"};
	std::vector<std::string> power_ups_component =
	  {"WeaponPowerUpComponent", "LifePowerUpComponent", "AttachPowerUpComponent"};
	this->_world->addSystem(new PowerUpSystem(power_ups, power_ups_component));
	this->_world->addSystem(new PlayerLifeSystem(3));
	this->_world->addSystem(new SFMLSetDisplayLiveSystem());

	CollisionSystem *collision;

	collision = new CollisionSystem();
	this->_world->addSystem(collision);
	this->_world->addEventHandler("CollisionEvent", collision, &LifeSystem::collision_event);

	EntityDeleterSystem *entityDeleterSystem = new EntityDeleterSystem();
	this->_world->addSystem(entityDeleterSystem);
	this->_world->addEventHandler("EntityDeletedEvent", entityDeleterSystem,
		&EntityDeleterSystem::addEntityToDelete);
	this->_world->addEventHandler("EntityDeletedEvent", entityDeleterSystem,
		&LifeSystem::delete_entity);
}

void		StateSoloGame::addSharedObjetcs()
{
	ComponentFactory *compos = new ComponentFactory();
	EntityFactory *entityFactory = new EntityFactory();

	compos->init();
	entityFactory->init();
	this->_world->setSharedObject("imageLoader", new ImageLoader());
	this->_world->setSharedObject("componentFactory", compos);
	this->_world->setSharedObject("entityFactory", entityFactory);
}

void		StateSoloGame::addEntities()
{
	EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");

	if (entityFactory == NULL)
		return;
	this->_world->addEntity(entityFactory->create("BACKGROUND_1"));
	this->_world->addEntity(entityFactory->create("BACKGROUND_2"));
	this->_world->addEntity(entityFactory->create("BORDER_SPAWNER_BOTTOM"));
	this->_world->addEntity(entityFactory->create("BORDER_SPAWNER_TOP"));
	this->_world->addEntity(entityFactory->create("GAME"));
	this->_world->addEntity(entityFactory->create("PLAYER_RED"));
	this->_world->addEntity(entityFactory->create("LIFE_DISPLAY"));
	this->_world->addEntity(entityFactory->create("POWERUP_FORCE"));
	//this->_world->addEntity(entityFactory->create("MONSTER_SPAWNER"));
	// this->_world->addEntity(entityFactory->create("MONSTER_SPAWNER"));
}

void		StateSoloGame::update(StateManager &manager)
{
  if (!this->_world->isRunning())
    manager.exit();
}

void		StateSoloGame::render(const Timer&timer)
{
	this->_world->process(timer.getDeltaTime() / 1000000.f);
}
