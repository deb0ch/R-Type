#ifndef ENTITY_H_
# define ENTITY_H_

# include	<vector>

# include	"IComponent.hh"

class		Entity
{
public:
  unsigned long			_id;
  std::vector<IComponent*>	_components;

  Entity();
  Entity(const Entity&);
  ~Entity();
  Entity&	operator=(const Entity&);

  void		addComponent(IComponent *);
};

#endif /* !ENTITY_H_ */
