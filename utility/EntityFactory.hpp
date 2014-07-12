#ifndef ENTITYFACTORY_H_
# define ENTITYFACTORY_H_

# include <string>

# include "DirectoryLister.hh"
# include "Entity.hh"
# include "EntityFile.hh"
# include "Factory.hpp"
# include "Hash.hh"

# include "ActionComponent.hh"
# include "AutoDestructComponent.hh"
# include "Box2DComponent.hh"
# include "CollisionComponent.hh"
# include "CollisionPowerComponent.hh"
# include "EntitySpawnerComponent.hh"
# include "ExplosionComponent.hh"
# include "FireAlwaysComponent.hh"
# include "Friction2DComponent.hh"
# include "LifeComponent.hh"
# include "LifePowerUpComponent.hh"
# include "MoveForwardComponent.hh"
# include "MovementLimitFrame2DComponent.hh"
# include "MovementSpeedComponent.hh"
# include "MoveSequenceComponent.hh"
# include "Pos2DComponent.hh"
# include "MoveFollowComponent.hh"
# include "NetworkReceiveActionComponent.hh"
# include "NetworkSendUpdateComponent.hh"
# include "SFMLInputComponent.hh"
# include "SFMLSpriteComponent.hh"
# include "Speed2DComponent.hh"
# include "TagComponent.hh"
# include "TeamComponent.hh"
# include "WeaponPowerUpComponent.hh"

static const	std::string path_files = "/home/ubuntu/rendu/epitech-r-type/Ressources/entities";

class EntityFactory : public Factory<Entity, hash_t>
{
  std::vector<std::string>	_keys;

public:
  EntityFactory()
  {}

  virtual ~EntityFactory()
  {}

  void	addEntity(const std::string &key, Entity *input)
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

  void	deserializeAll()
  {
    EntityFile				ef;
    DirectoryLister			directory_lister;
    std::ifstream			input;
    std::pair<std::string, Entity*>	res;

    std::vector<std::string> files = directory_lister.listDirectory(path_files + "/");
    for(auto it = files.begin(); it != files.end(); ++it)
      {
	if ((*it).substr((*it).rfind('.')) != ".entity")
	  return ;
	input.open(path_files + "/" + *it);
	try
	  {
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

  void	init()
  {
    this->deserializeAll();
  }
};

#endif /* !ENTITYFACTORY_H_ */
