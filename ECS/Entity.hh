#ifndef ENTITY_H_
# define ENTITY_H_

# include	<vector>
# include	<string>
# include	<iostream>
# include	<algorithm>
# include	<fstream>

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

  template <typename T, typename U>
  IComponent	*getComponent(const T &value, const U &hash) const
  {
    auto iterator = std::find_if(this->_components.begin(), this->_components.end(),
				 [&hash, &value] (const IComponent *component) -> bool
				 {
				   return (hash(component->getType()) == value);
				 });

    if (iterator == this->_components.end())
      return (NULL);
    return (*iterator);
  }

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
    if (!(tmp = dynamic_cast<T*>(component)))
      {
	std::cerr << ": Invalid type" << std::endl;
	abort();
      }
    return (tmp);
  }

  template <typename X, typename T, typename U>
  X		*getComponent(const T &value, const U &hash) const
  {
    IComponent	*component;
    X		*tmp;

    if (!(component = this->getComponent(value, hash)))
      return (NULL);
    if (!(tmp = dynamic_cast<X*>(component)))
      {
	std::cerr << ": Invalid type" << std::endl;
	abort();
      }
    return (tmp);
  }

  unsigned int	getId() const;
  Entity*	clone() const;
};

#endif /* !ENTITY_H_ */
