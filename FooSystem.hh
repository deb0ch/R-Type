#ifndef FOOSYSTEM_H_
# define FOOSYSTEM_H_

# include "ASystem.hh"

class		FooSystem : public ASystem
{
public:
		FooSystem();
		FooSystem(const FooSystem&);
		~FooSystem();
  FooSystem&	operator=(const FooSystem&);

protected:
  virtual void	processEntity(Entity *);
  virtual bool	canProcess(Entity *);
};

#endif /* !FOOSYSTEM_H_ */
