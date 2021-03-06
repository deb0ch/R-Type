#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include <string>

# include "Factory.hpp"
# include "ASerializableComponent.hh"
# include "SFMLInputComponent.hh"
# include "SFMLSoundComponent.hh"
# include "Friction2DComponent.hh"
# include "Box2DComponent.hh"
# include "Pos2DComponent.hh"
# include "Speed2DComponent.hh"
# include "MovementSpeedComponent.hh"
# include "SFMLSpriteComponent.hh"
# include "NetworkSendUpdateComponent.hh"
# include "ActionComponent.hh"
# include "NetworkSendActionComponent.hh"
# include "SyncPos2DComponent.hh"
# include "MovementSpeedComponent.hh"
# include "MoveForwardComponent.hh"
# include "MoveSequenceComponent.hh"
# include "MoveFollowComponent.hh"
# include "TagComponent.hh"
# include "MovementLimitFrame2DComponent.hh"
# include "Hash.hh"
# include "CollisionComponent.hh"
# include "CollisionPoint.hh"
# include "CollisionPowerComponent.hh"
# include "TeamComponent.hh"
# include "ExplosionComponent.hh"
# include "LifeComponent.hh"
# include "AutoDestructComponent.hh"
# include "NetworkReceiveActionComponent.hh"
# include "EntitySpawnerComponent.hh"
# include "FireAlwaysComponent.hh"
# include "WeaponPowerUpComponent.hh"
# include "LifePowerUpComponent.hh"
# include "SFMLTextComponent.hh"
# include "SFMLJoystickComponent.hh"
# include "AttachPowerUpComponent.hh"
# include "AttachedToComponent.hh"

class ComponentFactory : public Factory<ASerializableComponent, hash_t>
{
private :
  void addComponent(ASerializableComponent *input)
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
    this->addComponent(new ActionComponent());
    this->addComponent(new AttachedToComponent());
    this->addComponent(new AttachPowerUpComponent());
    this->addComponent(new AutoDestructComponent());
    this->addComponent(new Box2DComponent());
    this->addComponent(new CollisionComponent());
    this->addComponent(new CollisionPoint());
    this->addComponent(new CollisionPowerComponent());
    this->addComponent(new EntitySpawnerComponent());
    this->addComponent(new ExplosionComponent());
    this->addComponent(new FireAlwaysComponent());
    this->addComponent(new Friction2DComponent());
    this->addComponent(new LifeComponent());
    this->addComponent(new LifePowerUpComponent());
    this->addComponent(new MoveForwardComponent());
    this->addComponent(new MovementSpeedComponent());
    this->addComponent(new MoveFollowComponent());
    this->addComponent(new MoveSequenceComponent());
    this->addComponent(new MovementLimitFrame2DComponent());
    this->addComponent(new NetworkReceiveActionComponent());
    this->addComponent(new NetworkSendActionComponent());
    this->addComponent(new NetworkSendUpdateComponent());
    this->addComponent(new Pos2DComponent());
    this->addComponent(new SFMLInputComponent());
    this->addComponent(new SFMLJoystickComponent());
    this->addComponent(new SFMLSoundComponent());
    this->addComponent(new SFMLTextComponent());
    this->addComponent(new SFMLSpriteComponent());
    this->addComponent(new Speed2DComponent());
    this->addComponent(new SyncPos2DComponent());
    this->addComponent(new TagComponent());
    this->addComponent(new TeamComponent());
    this->addComponent(new WeaponPowerUpComponent());
  }

  virtual ASerializableComponent	*create(const std::string &key) const
  {
    return this->create(Hash()(key));
  }

  virtual ASerializableComponent	*create(const hash_t &key) const
  {
    const ASerializableComponent *tmp;

    tmp = this->getOriginal(key);
    if (!tmp)
      return NULL;
    return (tmp->cloneSerializable());
  }
};

#endif
