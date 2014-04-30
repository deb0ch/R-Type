#ifndef FOOSYSTEM_H_
# define FOOSYSTEM_H_

#include	"ISystem.hh"

class		FooSystem : public ISystem
{
protected:

public:
  FooSystem();
  FooSystem(const FooSystem&);
  ~FooSystem();
  FooSystem&	operator=(const FooSystem&);

  virtual void	process(std::vector<Entity *>&);
};

#endif /* !FOOSYSTEM_H_ */
