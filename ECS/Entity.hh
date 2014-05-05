#ifndef ENTITY_H_
# define ENTITY_H_

# include	<vector>
# include	<string>
# include	<iostream>

# include	"IComponent.hh"

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

  /** @see Entity::removeComponent(const std::string &type) */
  Entity	*removeComponent(IComponent *);
  Entity	*removeComponent(const std::string &id);

  bool		hasComponent(const std::string &string_type) const;
  /** @see Entity::getComponent(const std::string &type) */
  IComponent	*getComponent(const std::string &string_type) const;

  /**
   * @todo Throw an exception if the return if null.
   */
  template <typename T>
  T		*getComponent(const std::string &string_type) const
  {
    IComponent	*component;
    T		*tmp;

    if (!(component = this->getComponent(string_type)))
      return (NULL);
    if (!(tmp = dynamic_cast<T*>(component)))
      std::cerr << ": Invalid type" << std::endl;
    return (tmp);
  }
};

#endif /* !ENTITY_H_ */
