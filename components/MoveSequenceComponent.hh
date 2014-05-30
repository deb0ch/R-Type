#ifndef MOVESEQUENCECOMPONENT_H_
# define MOVESEQUENCECOMPONENT_H_

# include	 <string>
# include	"ACopyableComponent.hpp"
# include	"Entity.hh"
# include	"World.hh"

class		MoveSequenceComponent : public ACopyableComponent<MoveSequenceComponent>
{
public:
  MoveSequenceComponent(const std::vector<std::string> &actions = {}, const unsigned int tickToChange = 20);
  virtual	~MoveSequenceComponent();

  void  incrementTick();
  const std::string	&getAction() const;
  virtual void		serialize(IBuffer &) const;
  virtual void		unserialize(IBuffer &);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  std::vector<std::string>	_actions;
  unsigned int			_index;
  unsigned int			_tick;
  unsigned int			_tickToChange;

};

#endif /* !MOVEMENTSEQUENCECOMPONENT_H_ */
