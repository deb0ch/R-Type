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
  virtual	~Entity();
  Entity&	operator=(const Entity&);

  Entity	*addComponent(IComponent *);

  Entity	*removeComponent(IComponent *);
  Entity	*removeComponent(const std::string &id);

  bool		hasComponent(const std::string &string_type) const;
  IComponent	*getComponent(const std::string &string_type) const;

  template <typename T>
  T		*getComponent(const std::string &string_type) const
  {
    IComponent	*component;

    if (!(component = this->getComponent(string_type)))
      return (NULL);
    return (dynamic_cast<T*>(component));
  }
};

#endif /* !ENTITY_H_ */
