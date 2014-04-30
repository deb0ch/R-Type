#ifndef ISYSTEM_H_
# define ISYSTEM_H_

# include		<vector>
# include		"Entity.hh"

class			World;

class			ISystem
{
protected:
  /* Defined system MUST implement those methods */
  virtual bool		canProcess(Entity *) = 0;
  virtual void		processEntity(Entity *) = 0;

public:
			ISystem() {};
  virtual		~ISystem() {};

  virtual unsigned int	getPriority() const = 0;

  virtual void		setWorld(World *) = 0;

  virtual void		process(std::vector<Entity *>&) = 0;
};

#endif /* !ISYSTEM_H_ */
