#ifndef BARSYSTEM_H_
# define BARSYSTEM_H_

# include "ASystem.hh"

class		BarSystem : public ASystem
{
public:
		BarSystem();
		BarSystem(const BarSystem&);
		~BarSystem();
  BarSystem&	operator=(const BarSystem&);

protected:
  virtual void	processEntity(Entity *);
  virtual bool	canProcess(Entity *);
  virtual void	sortEntities(std::vector<Entity *>&);
};

#endif /* !BARSYSTEM_H_ */
