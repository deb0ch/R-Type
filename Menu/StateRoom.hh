#ifndef STATEROOM_H_
# define STATEROOM_H_

#include	"SFML/Audio/Music.hpp"

#include	"IState.hh"
#include	"SFML/Graphics.hpp"
#include	"SFMLButton.hh"
#include	"SFMLTextBox.hh"
#include	"World.hh"
#include	"LockVector.hpp"

class StateRoom : public IState
{
public:
	StateRoom(sf::RenderWindow * window, World *world, sf::Music *);
	virtual ~StateRoom();

	virtual void update(StateManager&);
	virtual void render(const Timer&);

protected:
	void init();
	void accessRoom();
	bool parsePacket(LockVector<IBuffer *> &vector, LockVector<IBuffer *>::iterator &it);

	World		*_world;
	sf::Sprite *_background;
	sf::Sprite *_logo;
	SFMLButton *_buttonplay;
	SFMLTextBox *_textboxRoom;
	SFMLTextBox *_serverRooms;
	sf::RenderWindow *_window;
	sf::Music	*_music;
	bool		_isConnecting;
};

#endif /* !STATEROOM_H_ */
