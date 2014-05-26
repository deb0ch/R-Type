#ifndef ENTITYFACTORY_H_
# define ENTITYFACTORY_H_

# include <string>
# include "Factory.hpp"
# include "SFMLInputComponent.hh"
# include "Friction2DComponent.hh"
# include "Box2DComponent.hh"
# include "Pos2DComponent.hh"
# include "TeamComponent.hh"
# include "Speed2DComponent.hh"
# include "MovementSpeedComponent.hh"
# include "SFMLSpriteComponent.hh"
# include "NetworkSendUpdateComponent.hh"
# include "ActionComponent.hh"
# include "PlayerMovementComponent.hh"
# include "CollisionPowerComponent.hh"
# include "Entity.hh"
# include "LifeComponent.hh"
# include "MoveForwardComponent.hh"
# include "FireAlwaysComponent.hh"
# include "MoveSequenceComponent.hh"
# include "EntitySpawnerComponent.hh"
# include "MovementLimitFrame2DComponent.hh"
# include "TagComponent.hh"
# include "CollisionComponent.hh"
# include "AutoDestructComponent.hh"
# include "MoveFollowComponent.hh"
# include "ExplosionComponent.hh"
# include "Hash.hh"
# include "NetworkReceiveActionComponent.hh"

class EntityFactory : public Factory<Entity, hash_t>
{
public:
  EntityFactory()
  {}

  virtual ~EntityFactory()
  {}

  void		addEntity(const std::string &key, Entity *input)
  {
    this->add(Hash()(key), input);
  }

  Entity*	create(const std::string &key) const
  {
    return this->create(Hash()(key));
  }

  Entity*	create(const std::string &key)
  {
    return (this->create(Hash()(key)));
  }

  virtual Entity*	create(const hash_t &key) const
  {
    const Entity	*tmp;

    tmp = this->getOriginal(key);
    if (!tmp)
      return NULL;
    return (tmp->clone());
  }

  void		initBackground()
  {
    this->addEntity("BACKGROUND_1", (new Entity())
		    ->addComponent((new TagComponent())
				   ->addTag("do_not_delete")
				   ->addTag("BackgroundSystem"))
		    ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		    ->addComponent(new Speed2DComponent(-75.f, 0.0f))
		    ->addComponent(new SFMLSpriteComponent("background.png", ImageLoader::NbSprite{ 1, 1 },
							   { { "", { 0, 0 } } })));

    this->addEntity("BACKGROUND_2", (new Entity())
		    ->addComponent((new TagComponent())
				   ->addTag("do_not_delete")
				   ->addTag("BackgroundSystem"))
		    ->addComponent(new Pos2DComponent(1095.0f, 0.0f))
		    ->addComponent(new Speed2DComponent(-75.f, 0.0f))
		    ->addComponent(new SFMLSpriteComponent("background.png", ImageLoader::NbSprite{ 1, 1 },
							   { { "", { 0, 0 } } })));
  }

  void		initOthers()
  {
    this->addEntity("EXPLOSION", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		    ->addComponent(new Speed2DComponent(-0.5f, 0.0f))
		    ->addComponent(new SFMLSpriteComponent("ExplosionSmall.png", ImageLoader::NbSprite{ 6, 1 },
							   { { "", { 0, 6 } } }, 5))
		    ->addComponent(new AutoDestructComponent(30))
		    );

    this->addEntity("BULLET_EXPLOSION", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		    ->addComponent(new Speed2DComponent(-0.5f, 0.0f))
		    ->addComponent(new SFMLSpriteComponent("smallExplosion.png", ImageLoader::NbSprite{ 6, 1 },
							   { { "", { 0, 6 } } }, 2))
		    ->addComponent(new AutoDestructComponent(12))
		    );

    this->addEntity("PLAYER_EXPLOSION", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		    ->addComponent(new Speed2DComponent(-0.5f, 0.0f))
		    ->addComponent(new Box2DComponent(100.0f, 100.0f))
		    ->addComponent(new SFMLSpriteComponent("ExplosionPlayer.png", ImageLoader::NbSprite{ 8, 1 },
							   { { "", { 2, 6 } } }))
		    ->addComponent(new AutoDestructComponent(60))
		    );

    this->addEntity("ALIEN_BOMB_EXPLOSION", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent(new Box2DComponent(100.0f, 100.0f))
		    ->addComponent(new CollisionPowerComponent(50))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 100.0f, 100.0f)))
		    ->addComponent(new SFMLSpriteComponent("Monster4.png", ImageLoader::NbSprite{ 4, 3 },
							   { { "", { 5, 3 } } }, 5))
		    ->addComponent(new AutoDestructComponent(15))
		    );

    this->addEntity("BOSS_EXPLOSION", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent(new Box2DComponent(250.0f, 280.0f))
		    ->addComponent(new CollisionPowerComponent(500))
		    ->addComponent(new SFMLSpriteComponent("BigExplosion.png", ImageLoader::NbSprite{ 10, 1 },
		    					   { { "", { 0, 5 } } }))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 250.0f, 280.0f)))
		    ->addComponent(new AutoDestructComponent(50))
		    );
  }

  void		initPlayer()
  {
    this->addEntity("PLAYER_BLUE", (new Entity())
		    ->addComponent(new NetworkReceiveActionComponent())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		    ->addComponent(new Box2DComponent(50.0f, 50.0f))
		    ->addComponent(new TeamComponent(1))
		    ->addComponent((new TagComponent())
				   ->addTag("PLAYER"))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new SFMLSpriteComponent("players.png",
							   ImageLoader::NbSprite{ 5, 5 },
							   { { "", { 2, 0 } },
							       { "UP", { 3, 2 } },
								 { "DOWN", { 0, 2 } } }))
		    ->addComponent(new SFMLInputComponent())
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 40.0f, 20.0f))
				   ->addToCollideItem("MONSTER")
				   ->addToCollideItem("PLAYER"))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new EntitySpawnerComponent({ {"BASIC_BULLET", 0} }, {}))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ->addAction("FIRE")
				   ));

    this->addEntity("PLAYER_PURPLE", (new Entity())
		    ->addComponent(new NetworkReceiveActionComponent())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		    ->addComponent(new Box2DComponent(50.0f, 50.0f))
		    ->addComponent(new TeamComponent(1))
		    ->addComponent((new TagComponent())
				   ->addTag("PLAYER"))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new SFMLSpriteComponent("players.png",
							   ImageLoader::NbSprite{ 5, 5 },
							   { { "", { 7, 0 } },
							       { "UP", { 8, 2 } },
								 { "DOWN", { 5, 2 } } }))
		    ->addComponent(new SFMLInputComponent())
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 40.0f, 20.0f))
				   ->addToCollideItem("MONSTER")
				   ->addToCollideItem("PLAYER"))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new EntitySpawnerComponent({ {"BASIC_BULLET", 0} }, {}))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ->addAction("FIRE")
				   ));

    this->addEntity("PLAYER_GREEN", (new Entity())
		    ->addComponent(new NetworkReceiveActionComponent())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		    ->addComponent(new Box2DComponent(50.0f, 50.0f))
		    ->addComponent(new TeamComponent(1))
		    ->addComponent((new TagComponent())
				   ->addTag("PLAYER"))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new SFMLSpriteComponent("players.png",
							   ImageLoader::NbSprite{ 5, 5 },
							   { { "", { 12, 0 } },
							       { "UP", { 13, 2 } },
								 { "DOWN", { 10, 2 } } }))
		    ->addComponent(new SFMLInputComponent())
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 40.0f, 20.0f))
				   ->addToCollideItem("MONSTER")
				   ->addToCollideItem("PLAYER"))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new EntitySpawnerComponent({ {"BASIC_BULLET", 0} }, {}))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ->addAction("FIRE")
				   ));

    this->addEntity("PLAYER_RED", (new Entity())
		    ->addComponent(new NetworkReceiveActionComponent())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new MovementLimitFrame2DComponent())
		    ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		    ->addComponent(new Box2DComponent(40.0f, 20.0f))
		    ->addComponent(new TeamComponent(1))
		    ->addComponent((new TagComponent())
				   ->addTag("PLAYER"))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new LifeComponent(200000, 20))
		    ->addComponent(new ExplosionComponent("PLAYER_EXPLOSION"))
		    ->addComponent(new SFMLSpriteComponent("players.png",
							   ImageLoader::NbSprite{ 5, 5 },
							   { { "", { 17, 0 } },
							       { "UP", { 18, 2 } },
								 { "DOWN", { 15, 2 } } }))
		    ->addComponent(new SFMLInputComponent())
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 40.0f, 20.0f))
				   ->addToCollideItem("MONSTER")
				   ->addToCollideItem("PLAYER"))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new EntitySpawnerComponent({ {"TRACKER_MISSILE", 0} }, {}, 0, 20,
							      { 40.0f, 0.0f }, { 40.0f, 0.0f }))
		    // ->addComponent(new EntitySpawnerComponent({ "BASIC_BULLET" }, {}, 0, 10,
		    // 					      { 40.0f, 0.0f }, { 40.0f, 0.0f }))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ->addAction("FIRE")
				   ));
  }

  void		initBullet()
  {
    this->addEntity("MONSTER_BASIC_BULLET", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(10.0f, 10.0f))
		    ->addComponent((new TagComponent())
				   ->addTag("BULLET"))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new CollisionPowerComponent(25))
		    ->addComponent(new LifeComponent(5))
		    ->addComponent(new SFMLSpriteComponent("ShotBasic.png",
							   ImageLoader::NbSprite{ 4, 1 },
							   { { "", { 0, 4 } } }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 10.0f, 10.0f))
				   ->addNotToCollideItem("BULLET"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));

    this->addEntity("MONSTER_BASIC_BULLET_3", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(10.0f, 10.0f))
		    ->addComponent((new TagComponent())
				   ->addTag("BULLET"))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new CollisionPowerComponent(25))
		    ->addComponent(new LifeComponent(5))
		    ->addComponent(new SFMLSpriteComponent("ShotBasic.png",
							   ImageLoader::NbSprite{ 4, 1 },
							   { { "", { 0, 4 } } }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT, MoveForwardComponent::DOWN))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 10.0f, 10.0f))
				   ->addNotToCollideItem("BULLET"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));

    this->addEntity("MONSTER_BASIC_BULLET_4", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(10.0f, 10.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent((new TagComponent())
				   ->addTag("BULLET"))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new CollisionPowerComponent(25))
		    ->addComponent(new LifeComponent(5))
		    ->addComponent(new SFMLSpriteComponent("ShotBasic.png",
							   ImageLoader::NbSprite{ 4, 1 },
							   { { "", { 0, 4 } } }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT, MoveForwardComponent::UP))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 10.0f, 10.0f))
				   ->addNotToCollideItem("BULLET")
				   ->addToCollideItem("PLAYER"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));

    this->addEntity("BOMB_BULLET_1", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(30.0f, 30.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent((new TagComponent())
				   ->addTag("BULLET")
				   ->addTag("BOMB"))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(120.f))
		    ->addComponent(new ExplosionComponent("ALIEN_BOMB_EXPLOSION"))
		    ->addComponent(new LifeComponent(200))
		    ->addComponent(new AutoDestructComponent(120))
		    ->addComponent(new SFMLSpriteComponent("Monster4.png",
							   ImageLoader::NbSprite{ 4, 3 },
							   { { "", { 4, 0 } } }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 10.0f, 10.0f))
				   ->addNotToCollideItem("BULLET"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));

    this->addEntity("BOMB_BULLET_2", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(30.0f, 30.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent((new TagComponent())
				   ->addTag("BULLET")
				   ->addTag("BOMB"))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(90.f))
		    ->addComponent(new ExplosionComponent("ALIEN_BOMB_EXPLOSION"))
		    ->addComponent(new LifeComponent(200))
		    ->addComponent(new AutoDestructComponent(120))
		    ->addComponent(new SFMLSpriteComponent("Monster4.png",
							   ImageLoader::NbSprite{ 4, 3 },
							   { { "", { 4, 0 } } }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT, MoveForwardComponent::UP))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 10.0f, 10.0f))
				   ->addNotToCollideItem("BULLET"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));

    this->addEntity("BOMB_BULLET_3", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(30.0f, 30.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent((new TagComponent())
				   ->addTag("BULLET")
				   ->addTag("BOMB"))
		    ->addComponent(new Speed2DComponent(0.0f, 0.0f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(90.f))
		    ->addComponent(new ExplosionComponent("ALIEN_BOMB_EXPLOSION"))
		    ->addComponent(new LifeComponent(200))
		    ->addComponent(new AutoDestructComponent(120))
		    ->addComponent(new SFMLSpriteComponent("Monster4.png",
							   ImageLoader::NbSprite{ 4, 3 },
							   { { "", { 4, 0 } } }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT, MoveForwardComponent::DOWN))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 10.0f, 10.0f))
				   ->addNotToCollideItem("BULLET"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));

    this->addEntity("BASIC_BULLET", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(20.0f, 20.0f))
		    ->addComponent(new TeamComponent(1))
		    ->addComponent((new TagComponent())
				   ->addTag("BULLET"))
		    ->addComponent(new ExplosionComponent("BULLET_EXPLOSION"))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(200.f))
		    ->addComponent(new CollisionPowerComponent(25))
		    ->addComponent(new LifeComponent(5))
		    ->addComponent(new SFMLSpriteComponent("ShotBig1.png",
							   ImageLoader::NbSprite{ 2, 1 },
							   { { "", { 1, 0 } } }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::RIGHT))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 20.0f, 20.0f))
				   ->addNotToCollideItem("BULLET"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));

    this->addEntity("TRACKER_MISSILE", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(30.0f, 30.0f))
		    ->addComponent(new TeamComponent(1))
		    ->addComponent(new Speed2DComponent(1000.0f, 0.0f))
		    ->addComponent(new Friction2DComponent(0.07f))
		    ->addComponent(new MovementSpeedComponent(60.f))
		    ->addComponent(new MoveFollowComponent("Ennemy"))
		    ->addComponent(new LifeComponent(100))
		    ->addComponent(new AutoDestructComponent(120))
		    ->addComponent(new ExplosionComponent("ALIEN_BOMB_EXPLOSION"))
		    ->addComponent(new SFMLSpriteComponent("Monster4.png",
							   ImageLoader::NbSprite{ 4, 3 },
							   { { "", { 4, 0 } } }))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 10.0f, 10.0f)))
		    ->addComponent(new CollisionPowerComponent(100))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ));
  }

  void		initMonster()
  {
    this->addEntity("MONSTER_1", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		    ->addComponent(new Box2DComponent(40.0f, 40.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent((new TagComponent())
				   ->addTag("Ennemy")
				   ->addTag("MONSTER"))
		    ->addComponent(new ExplosionComponent())
		    ->addComponent(new FireAlwaysComponent())
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new SFMLSpriteComponent("Monster1.png",
							   ImageLoader::NbSprite{ 8, 1 },
							   { { "", { 0, 8 } } }))
		    ->addComponent(new MovementSpeedComponent(150.f))
		    ->addComponent(new LifeComponent())
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 40.0f, 40.0f))
				   ->addToCollideItem("PLAYER")
				   ->addNotToCollideItem("MONSTER"))
		    ->addComponent(new CollisionPowerComponent(50))
		    ->addComponent(new EntitySpawnerComponent({ {"MONSTER_BASIC_BULLET", 0}, {"MONSTER_BASIC_BULLET_3", 0}, {"MONSTER_BASIC_BULLET_4", 0} }, {}, 0, 20))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT))
		    ->addComponent(new MoveSequenceComponent({"UP", "DOWN"}, 50))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ->addAction("FIRE"))
		    );

    this->addEntity("MONSTER_2", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		    ->addComponent(new Box2DComponent(50.0f, 50.0f))
		    ->addComponent(new TeamComponent())
		    ->addComponent((new TagComponent())
				   ->addTag("Ennemy")
				   ->addTag("MONSTER"))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.9f))
		    ->addComponent(new SFMLSpriteComponent("r-typesheet-7.png",
							   ImageLoader::NbSprite{ 4, 3 },
							   { { "", { 8, 4 } } }))
		    ->addComponent(new MovementSpeedComponent(50.f))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 50.0f, 50.0f))
				   ->addToCollideItem("PLAYER")
				   ->addNotToCollideItem("MONSTER"))
		    ->addComponent(new LifeComponent(500))
		    ->addComponent(new ExplosionComponent())
		    ->addComponent(new CollisionPowerComponent(50))
		    ->addComponent(new FireAlwaysComponent())
		    ->addComponent(new EntitySpawnerComponent({ {"BOMB_BULLET_1", 0}, {"BOMB_BULLET_2", 0}, {"BOMB_BULLET_3", 0} },
							      {}, 0, 60, { -10.0f, 0.0f }, { -10.0f, 0.0f }))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ->addAction("FIRE"))
		    );

    this->addEntity("MONSTER_SPAWNER", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(800.0f, 300.0f))
		    ->addComponent(new EntitySpawnerComponent({ {"MONSTER_1", 0}, {"MONSTER_2", 0} }, {}, 0, 75,
							      { (0.0f), (-270.0f) }, { (0.0f), (270.0f) }, true, false))
		    );
  }

  void		initBoss()
  {
    this->addEntity("MONSTER_FROM_BOSS", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		    ->addComponent(new Box2DComponent(40.0f, 25.0f))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent((new TagComponent())
				   ->addTag("MONSTER")
				   ->addTag("Ennemy"))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new SFMLSpriteComponent("Monster3.png",
							   ImageLoader::NbSprite{ 5, 1 },
							   {
							     { "", { 2, 0 } }
							   }))
		    ->addComponent(new MovementSpeedComponent(60.f))
		    ->addComponent(new LifeComponent(200))
		    ->addComponent(new FireAlwaysComponent())
		    ->addComponent(new ExplosionComponent())
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(0.0f, 0.0f, 40.0f, 25.0f))
				   ->addToCollideItem("PLAYER")
				   ->addNotToCollideItem("MONSTER"))
		    ->addComponent(new CollisionPowerComponent(50))
		    ->addComponent(new EntitySpawnerComponent({ {"MONSTER_BASIC_BULLET_3", 0}, {"MONSTER_BASIC_BULLET_4", 0} }, {}, 0, 30,
							      { (-40.0f), (0.0f) }, { (-40.0f), (0.0f) }, true))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT))
		    ->addComponent(new MoveSequenceComponent({"UP", "DOWN"}, 20))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   ->addAction("FIRE"))
		    );

    this->addEntity("BOSS_1", (new Entity())
		    ->addComponent(new NetworkSendUpdateComponent())
		    ->addComponent(new Pos2DComponent(700.0f, 590.0f))
		    ->addComponent(new Box2DComponent(130.0f, 205.0f))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new MovementSpeedComponent(60.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent((new TagComponent())
				   ->addTag("MONSTER")
				   ->addTag("Ennemy"))
		    ->addComponent(new ExplosionComponent("BOSS_EXPLOSION"))
		    ->addComponent(new FireAlwaysComponent())
		    ->addComponent(new LifeComponent(7500))
		    ->addComponent((new CollisionComponent())
				   ->addCollisionPoint(new CollisionPoint(-15.0f, -60.0f, 100.0f, 90.0f))
				   ->addCollisionPoint(new CollisionPoint(5.0f, 75.0f, 55.0, 50.0f))
				   ->addToCollideItem("PLAYER")
				   ->addToCollideItem("BULLET")
				   ->addNotToCollideItem("MONSTER"))
		    ->addComponent(new CollisionPowerComponent(100))
		    ->addComponent(new SFMLSpriteComponent("Boss.png",
							   ImageLoader::NbSprite{ 4, 9 },
							   { { "", { 4, 4 } } }))
		    ->addComponent(new MoveSequenceComponent({"UP", "DOWN"}, 185))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("DOWN")
				   ->addAction("FIRE"))
		    ->addComponent(new EntitySpawnerComponent({ {"MONSTER_FROM_BOSS", 0}, {"MONSTER_BASIC_BULLET_4", 0},
								{"MONSTER_BASIC_BULLET_3", 0}, {"MONSTER_BASIC_BULLET", 0} }, {}, 0, 40,
			{ (-5.0f), (0.0f) }, { (-5.0f), (0.0f) }, true, false))
		    );
  }

  void		init()
  {
    this->initBackground();
    this->initPlayer();
    this->initBullet();
    this->initMonster();
    this->initBoss();
    this->initOthers();
  }
};

#endif
