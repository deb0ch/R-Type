#ifndef TEAMCOMPONENT_H_
# define TEAMCOMPONENT_H_

# include <vector>

# include "AComponent.hpp"
# include "INetworkSerializableComponent.hh"

class TeamComponent : public AComponent<TeamComponent>, public INetworkSerializableComponent
{
public:
  TeamComponent(const unsigned int team = 0);
  virtual	~TeamComponent();

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  void setTeam(const unsigned int team);
  unsigned int getTeam() const;

protected:
  unsigned int _team;

};

#endif /* !TEAMCOMPONENT_H_ */
