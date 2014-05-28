#ifndef SFMLTEXTBOX_H_
# define SFMLTEXTBOX_H_

#include "SFML/Graphics.hpp"

class SFMLTextBox
{
public:
	SFMLTextBox(sf::RenderWindow *window, float posX, float posY,
		int charSize = 40, int maxCharacters = 16);
	~SFMLTextBox();

	void	draw();
	void	addCharacter(char character);
	void	removelastCharacter();

	const std::string &getString() const;
	void setString(const std::string & string);
	void setColor(const sf::Color &color);

protected:
	int					_charSize;
	int					_maxCharacters;
	std::string			_string;
	sf::Text			_text;
	sf::RectangleShape	_borders;
	sf::RenderWindow	*_window;
	sf::Font			*_font;
};

#endif /* !SFMLTEXTBOX_H_ */
