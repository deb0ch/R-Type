#ifndef ASYSTEM_H_
# define ASYSTEM_H_

# include		"ISystem.hh"

class			ASystem : public ISystem
{
protected:
  static const int	_default_priority = 20;
  unsigned int		_priority;
  World			*_world;

public:
			ASystem(unsigned int type = _default_priority);
  virtual		~ASystem();

  virtual unsigned int	getPriority() const;

  virtual void		setWorld(World *);

  virtual void		process(std::vector<Entity *>&);
};

#endif /* !ASYSTEM_H_ */
