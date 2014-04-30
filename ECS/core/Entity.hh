#ifndef ENTITY_H_
# define ENTITY_H_

# include	<vector>

# include	"IComponent.hh"
# include	<string>

class		Entity
{
public:
  unsigned long			_id;
  std::vector<IComponent*>	_components;

  Entity();
  Entity(const Entity&);
  ~Entity();
  Entity&	operator=(const Entity&);

  Entity	*addComponent(IComponent *);
  bool		removeComponent(IComponent *);
  bool		removeComponent(const std::string &id);
  IComponent	*hasComponent(const std::string &string_type) const;
};

#endif /* !ENTITY_H_ */
