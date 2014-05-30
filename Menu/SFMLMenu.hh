#ifndef SFMLMENU_H_
# define SFMLMENU_H_

#include	"IState.hh"
#include	"SFML/Graphics.hpp"
#include	"SFMLButton.hh"
#include	"SFMLTextBox.hh"
#include	"World.hh"

class SFMLMenu : public IState
{
private :
	SFMLMenu(const SFMLMenu &) = delete;
	SFMLMenu&	operator=(const SFMLMenu&) = delete;

public:
	SFMLMenu(World *world);
	SFMLMenu(World *world, sf::RenderWindow *window);
	virtual ~SFMLMenu();

	const std::string &getIpAddress() const;

	void connect();
	virtual void update(StateManager&);
	virtual void render(const Timer&);


protected:
	void init();

	World		*_world;
	sf::Sprite *_background;
	sf::Sprite *_logo;
	SFMLButton *_buttonplay;
	SFMLButton *_buttonCredit;
	SFMLTextBox *_textboxIP;
	SFMLTextBox *_ipServer;
	sf::RenderWindow *_window;
};

#endif /* !SFMLMENU_H_ */
