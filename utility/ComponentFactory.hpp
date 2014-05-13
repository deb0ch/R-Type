#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include "Factory.hpp"
# include "SFMLInputComponent.hh"
# include "IComponent.hh"
# include "Hash.hh"

class ComponentFactory : public Factory<IComponent, unsigned long>
{
public :
	ComponentFactory()
	{ }

	virtual ~ComponentFactory(){
	}

	virtual void init()
	{
		/*
		IComponent *input = new SFMLInputComponent();
		this->add(Hash()(input->getType()), input);

		input = new Pos2DComponent(0.0f, 100.0f);
		this->add(Hash()(input->getType()), input);

		input = new Friction2DComponent(0.5f);
		this->add(Hash()(input->getType()), input);

		input = new Box2DComponent(50.0f, 50.0f);
		this->add(Hash()(input->getType()), input);
		*/
	}
};

#endif