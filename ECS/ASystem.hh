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

  /* Defined system MUST implement those methods */
  virtual bool		canProcess(Entity *) = 0;
  virtual void		processEntity(Entity *) = 0;

  /* Theses method CAN be overloaded in the derived classes  */
  virtual void		sortEntities(std::vector<Entity *>&);

  virtual void		beforeProcess();
  virtual void		afterProcess();

public:
  ASystem() = delete;
  ASystem(const std::string &type, unsigned int priority = _default_priority);
  virtual		~ASystem();

  virtual const std::string	&getType() const;
  virtual unsigned int	getPriority() const;

  virtual void		setWorld(World *);

  virtual void		process(std::vector<Entity *>&);
  virtual void		start();
  virtual void		pause();
  virtual void		resume();
  virtual void		stop();
};

#endif /* !ASYSTEM_H_ */
