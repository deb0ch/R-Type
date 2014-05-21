#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

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
# include "Hash.hh"

class ComponentFactory : public Factory<IComponent, unsigned long>
{
private :
  void addComponent(IComponent *input)
  {
    this->add(Hash()(input->getType()), input);
  }

public :
  ComponentFactory()
  {}

  virtual ~ComponentFactory(){
  }

  virtual void init()
  {
    this->addComponent(new SFMLInputComponent());
    this->addComponent(new Pos2DComponent());
    this->addComponent(new Friction2DComponent());
    this->addComponent(new Box2DComponent());
    this->addComponent(new Speed2DComponent());
    this->addComponent(new MovementSpeedComponent());
    this->addComponent(new SFMLSpriteComponent());
    this->addComponent(new NetworkSendUpdateComponent());
    this->addComponent((new ActionComponent())
		       ->addAction("UP")
		       ->addAction("RIGHT")
		       ->addAction("DOWN")
		       ->addAction("LEFT"));
    this->addComponent(new PlayerMovementComponent());
  }
};

#endif
