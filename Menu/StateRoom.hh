#ifndef STATEROOM_H_
# define STATEROOM_H_

#include	"IState.hh"
#include	"SFML/Graphics.hpp"
#include	"SFMLButton.hh"
#include	"SFMLTextBox.hh"
#include	"World.hh"

class StateRoom : public IState
{
public:
	StateRoom(sf::RenderWindow * window, World *world, const std::string &);
	virtual ~StateRoom();

	virtual void update(StateManager&);
	virtual void render(const Timer&);

protected:
	void init();

	std::string	_ipAddress;
	World		*_world;
	sf::Sprite *_background;
	sf::Sprite *_logo;
	SFMLButton *_buttonplay;
	SFMLTextBox *_textboxRoom;
	SFMLTextBox *_serverRooms;
	sf::RenderWindow *_window;
};

#endif /* !STATEROOM_H_ */