#ifndef ISYSTEM_H_
# define ISYSTEM_H_

# include		<vector>
# include		"Entity.hh"
# include		"IEvent.hh"

class			World;

class			ISystem
{
public:
			ISystem() {};
  virtual		~ISystem() {};

  virtual unsigned int	getPriority() const = 0;
  virtual const std::string	&getType() const = 0;

  virtual void		setWorld(World *) = 0;

  virtual void		process(std::vector<Entity *>&, const float delta) = 0;
  virtual void		init() = 0;
  virtual void		start() = 0;
  virtual void		pause() = 0;
  virtual void		resume() = 0;
  virtual void		stop() = 0;
};

#endif /* !ISYSTEM_H_ */
