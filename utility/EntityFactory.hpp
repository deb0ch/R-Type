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
# include "WeaponPowerUpComponent.hh"
# include "Hash.hh"
# include "NetworkReceiveActionComponent.hh"
# include "EntityFile.hh"
# include "LifePowerUpComponent.hh"

# include "DirectoryLister.hh"

class EntityFactory : public Factory<Entity, hash_t>
{
  std::vector<std::string>	_keys;

public:
  EntityFactory()
  {}

  virtual ~EntityFactory()
  {}

  void		addEntity(const std::string &key, Entity *input)
  {
    this->add(Hash()(key), input);
    this->_keys.push_back(key);
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

  /*
  void			serializeAll()
  {
    EntityFile		ef;
    std::ofstream	output;

    std::for_each(this->_keys.begin(), this->_keys.end(), [this, &ef, &output](const std::string &key)
		  {
		        output.open("Ressources/entities/"+key+".entity");
			ef.serialize(this->create(key), key, output);
			output.close();
		  });
  }
  */

  void					deserializeAll()
  {
    EntityFile				ef;
    DirectoryLister			directory_lister;
    std::ifstream			input;
    std::pair<std::string, Entity*>	res;

    std::vector<std::string> files = directory_lister.listDirectory("Ressources/entities/");
    for(auto it = files.begin(); it != files.end(); ++it)
      {
	input.open("./Ressources/entities/" + *it);
	try {
	  res = ef.deserialize(input);
	}
	catch (EntityFileException &efe)
	  {
	    efe.setFilename(*it);
	    throw;
	  }
	this->addEntity(res.first, res.second);
	input.close();
      }
  }

  void		init()
  {
    this->deserializeAll();
  }
};

#endif
