#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include "SFML/Graphics.hpp"
# include "AComponent.hh"
# include "ImageLoader.hh"

class		SFMLSpriteComponent : public AComponent<SFMLSpriteComponent>
{
protected:
  std::string	_filaName;

public:
		SFMLSpriteComponent(const std::string &filename);
  virtual	~SFMLSpriteComponent();

  sf::Sprite	*getSprite(ImageLoader &imageLoader);
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
