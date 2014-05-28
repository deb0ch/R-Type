#ifndef SFMLMENU_H_
# define SFMLMENU_H_

#include	"SFML/Graphics.hpp"
#include	"SFMLButton.hh"
#include	"SFMLTextBox.hh"

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

	sf::Sprite *_background;
	SFMLButton *_buttonplay;
	SFMLTextBox *_textboxIP;
	sf::RenderWindow *_window;
};

#endif /* !SFMLMENU_H_ */
