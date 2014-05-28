#ifndef SFMLMENU_H_
# define SFMLMENU_H_

#include	"SFML/Graphics.hpp"
#include	"SFMLButton.hh"

class SFMLMenu
{
public:
	SFMLMenu();
	SFMLMenu(sf::RenderWindow *window);
	~SFMLMenu();

	sf::RenderWindow *getWindow() const;
	const std::string &getIpAddress() const;

	char update();
	void render();


protected:
	void init();

	std::string _ipAddress;

	sf::Sprite *_background;
	SFMLButton *_buttonplay;
	sf::RenderWindow *_window;
	sf::Font *_font;
};

#endif /* !COLLISIONEVENT_H_ */
