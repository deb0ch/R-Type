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
  std::vector<std::string>	_entities;
  std::vector<std::string>	_components;
  unsigned int			_next;
  unsigned long			_nb;
  unsigned long			_delay;
  std::pair<float, float>	_min_pos;
  std::pair<float, float>	_max_pos;
  bool				_random;
  bool				_abs;

  bool				_active;

  unsigned long			_counter;
  unsigned long			_tick;

public:
  EntitySpawnerComponent(std::vector<std::string> entities = {},
			 std::vector<std::string> components = {},
			 unsigned long nb = 0,
			 unsigned long delay = 15,
			 std::pair<float, float> min_pos = {0.0f, 0.0f},
			 std::pair<float, float> max_pos = {0.0f, 0.0f},
			 bool random = true,
			 bool abs = false);
  virtual	~EntitySpawnerComponent();

  void				setActive(bool active);
  Entity			*spawnEntity(EntityFactory *facto, const Pos2DComponent *pos = NULL);
  virtual void			serialize(IBuffer &) const;
  virtual void			unserialize(IBuffer &);
};

#endif /* !ENTITYSPAWNERCOMPONENT_H_ */
