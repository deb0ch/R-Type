#ifndef __MOVEMENTFORWARDCOMPONENT_H_
# define __MOVEMENTFORWARDCOMPONENT_H_

# include	"AComponent.hpp"
# include	"Entity.hh"
# include	"World.hh"

class		MoveForwardComponent : public AComponent<MoveForwardComponent>
{
public:
	enum Direction
	{
		UP,
		RIGHT,
		LEFT,
		DOWN,
	};

public:
	MoveForwardComponent(const Direction = LEFT);
	MoveForwardComponent(const Direction, const Direction);
	virtual	~MoveForwardComponent();

	const std::vector<std::string> &getDirection() const;
	void setDirection(const Direction);

protected:
	std::vector<std::string> _actions;
	unsigned int _index;
	Direction _direction;
};

#endif /* !MOVEMENTFORWARDCOMPONENT_H_ */
