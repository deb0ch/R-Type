#ifndef MOVESEQUENCECOMPONENT_H_
# define MOVESEQUENCECOMPONENT_H_

# include	 <string>
# include	"ACopyableComponent.hpp"
# include	"Entity.hh"
# include	"World.hh"

class		MoveSequenceComponent : public ACopyableComponent<MoveSequenceComponent>
{
public:
  MoveSequenceComponent(const std::vector<std::string> &actions = {}, float tickToChange = 0.5f);
  virtual	~MoveSequenceComponent();

  void  incrementTick(float delta);
  const std::string	&getAction() const;
  virtual void		serialize(IBuffer &) const;
  virtual void		unserialize(IBuffer &);

  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  std::vector<std::string>	_actions;
  unsigned int			_index;
  float				_tick;
  float				_tickToChange;

};

#endif /* !MOVEMENTSEQUENCECOMPONENT_H_ */
