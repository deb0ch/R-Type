#ifndef ASYSTEM_H_
# define ASYSTEM_H_

# include "ISystem.hh"

class ASystem : public ISystem
{
public:
		ASystem();
  virtual	~ASystem();

  virtual void	process(std::vector<Entity *>&);
};

#endif /* !ASYSTEM_H_ */
