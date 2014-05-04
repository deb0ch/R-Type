#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include	"SFML/Graphics.hpp"

# include	"AComponent.hh"

class		SFMLSpriteComponent : public AComponent
{
protected:
  const std::string	_filaName;

public:
		SFMLSpriteComponent(const std::string &filename);
		SFMLSpriteComponent(const SFMLSpriteComponent&);
  virtual	~SFMLSpriteComponent();
  SFMLSpriteComponent	&operator=(const SFMLSpriteComponent&);

  sf::Sprite	&getSprite() const;
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
