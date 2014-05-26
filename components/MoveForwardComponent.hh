#ifndef __MOVEMENTFORWARDCOMPONENT_H_
# define __MOVEMENTFORWARDCOMPONENT_H_

# include	"Entity.hh"
# include	"World.hh"
# include	"ACopyableComponent.hpp"

class		MoveForwardComponent : public ACopyableComponent<MoveForwardComponent>
{
public:
	enum Direction
	{
		UP,
		RIGHT,
		LEFT,
		DOWN,
		NONE
	};

public:
	MoveForwardComponent(const Direction = LEFT);
	MoveForwardComponent(const Direction, const Direction);
	virtual	~MoveForwardComponent();

	const std::vector<std::string> &getDirection() const;
	// void setDirection(const Direction);

	virtual void	serialize(IBuffer &) const;
	virtual void	unserialize(IBuffer &);

protected:
	std::vector<std::string> _actions;
	unsigned int _index;
	Direction _direction1;
	Direction _direction2;
};

#endif /* !MOVEMENTFORWARDCOMPONENT_H_ */
