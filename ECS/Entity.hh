#ifndef ENTITY_H_
# define ENTITY_H_

# include	<vector>
# include	<string>
# include	<iostream>

# include	"IComponent.hh"

class		Entity
{
public:
  unsigned int			_id;
  std::vector<IComponent*>	_components;

		Entity();
		Entity(const Entity&);
  virtual	~Entity();
  Entity&	operator=(const Entity&);

  Entity	*addComponent(IComponent *);

  /** @see Entity::removeComponent(const std::string &type) */
  Entity	*removeComponent(IComponent *);
  Entity	*removeComponent(const std::string &id);

  Entity	*removeAllComponent();
  Entity	*removeAllComponentExcept(const IComponent *);
  Entity	*removeAllComponentExcept(const std::string &id);

  bool		hasComponent(const std::string &string_type) const;
  /** @see Entity::getComponent(const std::string &type) */
  IComponent	*getComponent(const std::string &string_type) const;

  /**
   * @todo Throw an exception if the return is null.
   */
  template <typename T>
  T		*getComponent(const std::string &string_type) const
  {
    IComponent	*component;
    T		*tmp;

    if (!(component = this->getComponent(string_type)))
      return (NULL);
    std::cout << "aze: " << string_type << "." << std::endl;
    if (!(tmp = dynamic_cast<T*>(component)))
      {
	std::cerr << ": Invalid type" << std::endl;
	abort();
      }
    return (tmp);
  }
};

#endif /* !ENTITY_H_ */
