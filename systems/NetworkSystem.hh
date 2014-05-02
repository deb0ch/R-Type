#ifndef NETWORKSYSTEM_H_
# define NETWORKSYSTEM_H_

# include "ASystem.hh"

class NetworkSystem : public ASystem
{
public:
		NetworkSystem(const std::vector<std::string> &component_to_send);
  virtual	~NetworkSystem();

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float delta);
private:
  std::vector<std::string> _component_to_send;
};

#endif /* !NETWORKSYSTEM_H_ */
