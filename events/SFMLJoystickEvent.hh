#ifndef		SFMLJOYSTICKEVENT_H_
# define	SFMLJOYSTICKEVENT_H_

# include	"AEvent.hh"

class		SFMLJoystickEvent : public AEvent
{
public:
  enum JoystickButton {
    A		= 0,
    B		= 1,
    X		= 2,
    Y		= 3,
    L1		= 4,
    R1		= 5,
    SELECT	= 6,
    START	= 7,
    UP		= 8,
    RIGHT	= 9,
    DOWN	= 10,
    LEFT	= 11
  };

public:
  const unsigned int		_key;
  const bool			_active;

  SFMLJoystickEvent(const unsigned int key, const bool active);
  virtual ~SFMLJoystickEvent();


};

#endif /* !SFMLJOYSTICKEVENT_H_ */
