#ifndef		SFMLKEYEVENT_H_
# define	SFMLKEYEVENT_H_

# include	"SFML/Window/Keyboard.hpp"
# include	"AEvent.hh"

class		SFMLKeyEvent : public AEvent
{
public:
  const sf::Keyboard::Key	_key;
  const bool			_active;

  SFMLKeyEvent(const sf::Keyboard::Key key, const bool active);
  virtual ~SFMLKeyEvent();

};

#endif /* !SFMLKEYEVENT_H_ */
