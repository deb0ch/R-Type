#ifndef MOVESEQUENCECOMPONENT_H_
# define MOVESEQUENCECOMPONENT_H_

# include <string>
# include	"AComponent.hpp"
# include	"Entity.hh"
# include	"World.hh"

class		MoveSequenceComponent : public AComponent<MoveSequenceComponent>
{
public:
	enum Sens
	{
		UP_DOWN = 0,
		RIGHT_LEFT = 1
	};

public:
	MoveSequenceComponent(const Sens = UP_DOWN, const unsigned int tickToChange = 20);
	virtual	~MoveSequenceComponent();

	void  incrementTick();
	const std::string &getAction() const;

protected:
	std::vector<std::string> _actions;
	unsigned int _index;
	Sens _sens;
	unsigned int _tick;
	unsigned int _tickToChange;

};

#endif /* !MOVEMENTSEQUENCECOMPONENT_H_ */
