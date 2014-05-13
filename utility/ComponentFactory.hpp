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
		IComponent *input = new SFMLInputComponent();
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = new Pos2DComponent(400.0f, 300.0f);
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = new Friction2DComponent(0.5f);
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = new Box2DComponent(50.0f, 50.0f);
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = new Speed2DComponent(5.0f, 5.0f);
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = new MovementSpeedComponent(5);
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = new SFMLSpriteComponent(std::string("Ressources\\Images\\players.png"));
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = new NetworkSendUpdateComponent();
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);

		input = ((new ActionComponent())
			->addAction("UP")
			->addAction("RIGHT")
			->addAction("DOWN")
			->addAction("LEFT"));
		std::cout << input->getType() << std::endl;
		this->add(Hash()(input->getType()), input);
	}
};

#endif