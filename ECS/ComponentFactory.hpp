#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include <map>
# include "Factory.hpp"
# include "IComponent.hh"
# include "Hash.hh"

class ComponentFactory : public Factory<IComponent, unsigned long>
{
public:
	ComponentFactory()
	{ }

	virtual ~ComponentFactory(){
	}

	virtual void init()
	{
		//this->add(Hash()(new->getType()), input);
	}

private:
	std::string _directory;

};

#endif /* !COMPONENTFACTORY_H_ */
