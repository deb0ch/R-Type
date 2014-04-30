#ifndef ISYSTEM_H_
# define ISYSTEM_H_

# include	<vector>

# include	"Entity.hh"

class		ISystem
{
public:
		ISystem() {};
  virtual	~ISystem() {};

  virtual void	process(std::vector<Entity *>&) = 0;
};

#endif /* !ISYSTEM_H_ */
