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
#include	"BackgroundSystem.hh"

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

#include	"ImageLoader.hh"
#include	"ActionComponent.hh"

#include	"NetworkBuffer.hh"

#include	"ComponentFactory.hpp"

#include	"SoundLoader.hh"

#define PATH "Ressources/Images/"

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
	world.addSystem(new BackgroundSystem());
	world.addSystem(new ResetActionSystem());
	world.addSystem(new MoveSystem());
	world.addSystem(new Friction2DSystem());
	world.addSystem(new SFMLEventSystem());
	world.addSystem(new SFMLInputSystem());
	world.addSystem(new OutOfBoundsSystem());
	world.addSystem(new MoveFollowSystem());
	world.addSystem(new MoveForwardSystem());
	world.addSystem(new MoveSequenceSystem());
	world.addSystem(new ActionMovementSystem());
	world.addSystem(new SFMLRenderSystem());
	world.addSystem(new LifeSystem());

	CollisionSystem *collision;
	collision = new CollisionSystem();
	world.addSystem(collision);
	world.addEventHandler("CollisionEvent", collision, &LifeSystem::collision_event);

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
	"Friction2DComponent" };
	network = new NetworkSendUpdateSystem(arg);
	world.addSystem(network);
	world.addSystem(new NetworkReceiveUpdateSystem());
}

void		addSharedObjetcs(World &world)
{
	ComponentFactory *compos = new ComponentFactory();
	compos->init();
	world.setSharedObject("imageLoader", new ImageLoader());
	world.setSharedObject("componentFactory", compos);
}

void		addEntities(World &world)
{
	ComponentFactory *test = world.getSharedObject<ComponentFactory>("componentFactory");

	world.addEntity(world.createEntity()
			->addComponent((new TagComponent())
				       ->addTag("do_not_delete")
				       ->addTag("BackgroundSystem"))
			->addComponent(new Pos2DComponent(0.0f, 0.0f))
			->addComponent(new Speed2DComponent(-0.5f, 0.0f))
			->addComponent(new SFMLSpriteComponent(PATH + std::string("background.png"), ImageLoader::NbSprite{1, 1}, {{"", {0, 0}}})));


	world.addEntity(world.createEntity()
			->addComponent((new TagComponent())
				       ->addTag("do_not_delete")
				       ->addTag("BackgroundSystem"))
			->addComponent(new Pos2DComponent(1095, 0.0f))
			->addComponent(new Speed2DComponent(-0.5f, 0.0f))
			->addComponent(new SFMLSpriteComponent(PATH + std::string("background.png"), ImageLoader::NbSprite{1, 1}, {{"", {0, 0}}})));


	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(0.0f, 100.0f))
		->addComponent(new Box2DComponent(50.0f, 50.0f))
		->addComponent(new Speed2DComponent(5.f, 5.f))
		->addComponent(new Friction2DComponent(0.5f))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("players2.png"), ImageLoader::NbSprite{ 5, 5 },
		{ { "", { 2, 0 } },
		{ "DOWN", { 0, 2 } },
		{ "UP", { 3, 2 } } }))
		->addComponent(new SFMLInputComponent())
		->addComponent(new MovementSpeedComponent(5))
		->addComponent(new LifeComponent(500))
		->addComponent(new CollisionPowerComponent(100))
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("RIGHT")
		->addAction("DOWN")
		->addAction("LEFT")
		)
		);


	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(250.0f, 470.0f))
		->addComponent(new Box2DComponent(100.0f, 100.0f))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("r-typesheet36.png"), ImageLoader::NbSprite{ 2, 4 },
		{ { "", { 0, 8 } } }))
		->addComponent(new CollisionPowerComponent(10000))
		);

	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(600.0f, 500.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(5.f, 2.f))
		->addComponent(new Friction2DComponent(0.3f))
		->addComponent(new MovementSpeedComponent(1.0f))
		->addComponent(new CollisionPowerComponent(50))
		->addComponent(new LifeComponent())
		->addComponent(new SFMLSpriteComponent(PATH + std::string("ShotBoss.png"),
		ImageLoader::NbSprite{ 4, 1 },
		{ { "", { 0, 4 } } }))
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("RIGHT")
		->addAction("DOWN")
		->addAction("LEFT")
		)
		->addComponent(new MoveFollowComponent(world.getEntity(1)->_id))
		);
	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(100.0f, 200.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(5.f, 2.f))
		->addComponent(new Friction2DComponent(0.9f))
		->addComponent(new MovementSpeedComponent(0.8f))
		->addComponent(new PlayerMovementComponent())
		->addComponent(new CollisionPowerComponent(50))
		->addComponent(new LifeComponent())
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("RIGHT")
		->addAction("DOWN")
		->addAction("LEFT")
		)
		->addComponent(new MoveFollowComponent(world.getEntity(1)->_id))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("ShotBoss.png"),
		ImageLoader::NbSprite{ 4, 1 },
		{ { "", { 0, 4 } } }, 1))
		);

	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(000.0f, 400.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(5.f, 2.f))
		->addComponent(new Friction2DComponent(0.6f))
		->addComponent(new MovementSpeedComponent(0.8f))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("r-typesheet-16.png"),
		ImageLoader::NbSprite{ 6, 1 },
		{ { "", { 3, 3 } } }))
		->addComponent(new MoveForwardComponent(MoveForwardComponent::RIGHT, MoveForwardComponent::UP))
		->addComponent(new MoveSequenceComponent(MoveSequenceComponent::UP_DOWN, 50))
		->addComponent(new LifeComponent())
		->addComponent(new CollisionPowerComponent(50))
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("RIGHT")
		->addAction("DOWN")
		)
		);

	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(600.0f, 250.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(5.f, 2.f))
		->addComponent(new Friction2DComponent(0.6f))
		->addComponent(new MovementSpeedComponent(0.8f))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("r-typesheet-16.png"),
		ImageLoader::NbSprite{ 6, 1 },
		{ { "", { 0, 3 } } }))
		->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT))
		->addComponent(new MoveSequenceComponent(MoveSequenceComponent::UP_DOWN, 25))
		->addComponent(new LifeComponent())
		->addComponent(new CollisionPowerComponent(50))
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("DOWN")
		->addAction("LEFT")
		)
		);


	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(550.0f, 280.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(5.f, 2.f))
		->addComponent(new Friction2DComponent(0.6f))
		->addComponent(new MovementSpeedComponent(0.5f))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("r-typesheet-7.png"),
		ImageLoader::NbSprite{ 4, 3 },
		{ { "", { 8, 4 } } }))
		->addComponent(new MoveSequenceComponent(MoveSequenceComponent::UP_DOWN, 140))
		->addComponent(new LifeComponent())
		->addComponent(new CollisionPowerComponent(50))
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("DOWN")
		)
		);
	world.addEntity(world.createEntity()
		->addComponent(new Pos2DComponent(600.0f, 300.0f))
		->addComponent(new Box2DComponent(10.0f, 10.0f))
		->addComponent(new Speed2DComponent(5.f, 2.f))
		->addComponent(new Friction2DComponent(0.6f))
		->addComponent(new MovementSpeedComponent(0.5f))
		->addComponent(new SFMLSpriteComponent(PATH + std::string("r-typesheet-7.png"),
		ImageLoader::NbSprite{ 4, 3 },
		{ { "", { 8, 4 } } }, 2))
		->addComponent(new MoveSequenceComponent(MoveSequenceComponent::UP_DOWN, 150))
		->addComponent(new LifeComponent())
		->addComponent(new CollisionPowerComponent(50))
		->addComponent((new ActionComponent())
		->addAction("UP")
		->addAction("DOWN")
		)
		);

}

int			main()
{
	World		world;

	registerComponents(world);
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
