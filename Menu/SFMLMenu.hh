#ifndef SFMLMENU_H_
# define SFMLMENU_H_

#include "SFML/Graphics.hpp"

class SFMLMenu
{
public:
	SFMLMenu();
	SFMLMenu(sf::RenderWindow *window);
	~SFMLMenu();

	sf::RenderWindow *getWindow() const;

	char update();
	void render();

protected:
	std::string _ipAdress;
	sf::RenderWindow *_window;
};

#endif /* !COLLISIONEVENT_H_ */
