#ifndef TEAMCOMPONENT_H_
# define TEAMCOMPONENT_H_

# include <vector>

# include "ACopyableComponent.hpp"

class TeamComponent : public ACopyableComponent<TeamComponent>
{
public:
  TeamComponent(const unsigned int team = 0);
  virtual	~TeamComponent();

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  void setTeam(const unsigned int team);
  unsigned int getTeam() const;

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  unsigned int _team;

};

#endif /* !TEAMCOMPONENT_H_ */
