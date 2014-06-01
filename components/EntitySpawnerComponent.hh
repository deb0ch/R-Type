#ifndef ENTITYSPAWNERCOMPONENT_H_
# define ENTITYSPAWNERCOMPONENT_H_

# include	<vector>
# include	<string>

# include	"ACopyableComponent.hpp"

# include	"Entity.hh"
# include	"Pos2DComponent.hh"

class		EntityFactory;

class		EntitySpawnerComponent : public ACopyableComponent<EntitySpawnerComponent>
{
protected:
  std::vector<std::pair<std::string, unsigned int>>	_entities;
  unsigned int			_maxWeight;
  std::vector<IComponent*>	_components;
  unsigned int			_next;
  unsigned long			_nb;
  float				_delay;
  std::pair<float, float>	_min_pos;
  std::pair<float, float>	_max_pos;
  bool				_random;
  bool				_abs;

  bool				_active;

  unsigned long			_counter;
  float				_tick;
  std::string			_lastSpawned;

  void				fixWeights();

public:
  EntitySpawnerComponent(const std::vector<std::pair<std::string, unsigned int>> &entities = {},
			 const std::vector<IComponent*> &components = {},
			 unsigned long nb = 0,
			 float delay = 0.25f,
			 const std::pair<float, float> &min_pos = {0.0f, 0.0f},
			 const std::pair<float, float> &max_pos = {0.0f, 0.0f},
			 bool random = true,
			 bool abs = false);
  EntitySpawnerComponent(const EntitySpawnerComponent& ref);
  virtual	~EntitySpawnerComponent();

  bool				isAbsolute() const;
  const std::pair<float, float>		getCoordinates() const;
  const std::vector<IComponent*>	&getComponents() const;

  void				setActive(bool active);
  Entity			*spawnEntity(EntityFactory *facto, float delta);
  void				clearEntities();
  void				setDelay(float delay);
  void				addEntity(const std::pair<std::string, unsigned int> &);
  const std::string		&getLastSpawned() const;
  float				getDelay() const;

  virtual void			serialize(IBuffer &) const;
  virtual void			unserialize(IBuffer &);

  virtual void			deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void			serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !ENTITYSPAWNERCOMPONENT_H_ */
