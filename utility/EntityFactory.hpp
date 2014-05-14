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
# include "Hash.hh"

class EntityFactory : public Factory<Entity, unsigned long>
{
public :
  EntityFactory()
  {}

  virtual ~EntityFactory()
  {}

  void		addEntity(Entity *input, const std::string &key)
  {
    this->add(Hash()(key), input);
  }

  Entity*	create(const std::string &key)
  {
    return (this->Factory::create(Hash()(key)));
  }

  void		init()
  {
    this->addEntity(new Entity(), "PLAYER");

    this->addEntity((new Entity())
		    ->addComponent(new Pos2DComponent(300.0f, 000.0f))
		    ->addComponent(new Box2DComponent(10.0f, 10.0f))
		    ->addComponent(new Speed2DComponent(20.f, 5.f))
		    ->addComponent(new SFMLSpriteComponent("players.png"))
      , "TEST");
  }
};

#endif
