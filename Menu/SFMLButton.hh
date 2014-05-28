#ifndef SFMLBUTTON_H_
# define SFMLBUTTON_H_

#include "SFML/Graphics.hpp"

class SFMLButton
{
public:
	SFMLButton(sf::RenderWindow *window, int posX, int posY, int width, int height);
	~SFMLButton();

	void	addTexture(const std::string &path, int width, int height);
	void	draw();
	bool	isMouseOnButton();

protected:
	sf::RenderWindow *_window;
	sf::RectangleShape *_button;
};

#endif /* !SFMLBUTTON_H_ */
