#ifndef ASYSTEM_H_
# define ASYSTEM_H_

# include		"ISystem.hh"

class			ASystem : public ISystem
{
protected:
  static const int	_default_priority = 20;

  std::string		_type;
  unsigned int		_priority;
  World			*_world;

public:
  ASystem() = delete;
  ASystem(const std::string &type, unsigned int priority = _default_priority);
  virtual		~ASystem();

  virtual const std::string	&getType() const;
  virtual unsigned int	getPriority() const;

  virtual void		setWorld(World *);

  virtual void		process(std::vector<Entity *>&);
  virtual void		sortEntities(std::vector<Entity *> &) = 0;
};

#endif /* !ASYSTEM_H_ */
