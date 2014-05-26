#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include <string>
# include "Factory.hpp"
# include "ASerializableComponent.hh"
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
# include "NetworkSendActionComponent.hh"
# include "Hash.hh"

class ComponentFactory : public Factory<ASerializableComponent, unsigned long>
{
private:
	void addComponent(ASerializableComponent *input)
	{
		this->add(Hash()(input->getType()), input);
	}

public:
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
		this->addComponent(new ActionComponent());
		this->addComponent(new PlayerMovementComponent());
		this->addComponent(new NetworkSendActionComponent());
	}

	virtual ASerializableComponent	*create(const unsigned long &key) const
	{
		const ASerializableComponent *tmp;

		tmp = this->getOriginal(key);
		if (!tmp)
			return NULL;
		return (tmp->cloneSerializable());
	}
};

#endif