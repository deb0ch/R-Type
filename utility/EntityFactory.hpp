#ifndef ENTITYFACTORY_H_
# define ENTITYFACTORY_H_

# include <string>
# include "Factory.hpp"
# include "SFMLInputComponent.hh"
# include "Friction2DComponent.hh"
# include "Box2DComponent.hh"
# include "Pos2DComponent.hh"
# include "Speed2DComponent.hh"
# include "MovementSpeedComponent.hh"
# include "SFMLSpriteComponent.hh"
# include "NetworkSendUpdateComponent.hh"
# include "ActionComponent.hh"
# include "PlayerMovementComponent.hh"
# include "Entity.hh"
# include "LifeComponent.hh"
# include "MoveForwardComponent.hh"
# include "MoveSequenceComponent.hh"
# include "EntitySpawnerComponent.hh"
# include "Hash.hh"

class EntityFactory : public Factory<Entity, unsigned long>
{
public :
  EntityFactory()
  {}

  virtual ~EntityFactory()
  {}

  void		addEntity(const std::string &key, Entity *input)
  {
    this->add(Hash()(key), input);
  }

  Entity*	create(const std::string &key)
  {
    return (this->Factory::create(Hash()(key)));
  }

  void		init()
  {
    this->addEntity("PLAYER", (new Entity()));

    this->addEntity("TEST_SPAWN", (new Entity())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(10.0f, 10.0f))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(0.5f))
		    ->addComponent(new LifeComponent(20))
		    ->addComponent(new SFMLSpriteComponent("players.png"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   )
		    //->addComponent(new EntitySpawnerComponent({"TEST_SPAWN"}))
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::LEFT))
		    );

    this->addEntity("TEST_BULLET", (new Entity())
		    ->addComponent(new Pos2DComponent(300.0f, 300.0f))
		    ->addComponent(new Box2DComponent(10.0f, 10.0f))
		    ->addComponent(new Speed2DComponent(0.f, 0.f))
		    ->addComponent(new Friction2DComponent(0.5f))
		    ->addComponent(new MovementSpeedComponent(3.f))
		    ->addComponent(new LifeComponent(5))
		    ->addComponent(new SFMLSpriteComponent("players.png"))
		    ->addComponent((new ActionComponent())
				   ->addAction("UP")
				   ->addAction("RIGHT")
				   ->addAction("DOWN")
				   ->addAction("LEFT")
				   )
		    ->addComponent(new MoveForwardComponent(MoveForwardComponent::RIGHT))
		    );
  }
};

#endif
