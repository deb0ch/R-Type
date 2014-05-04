#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include	"SFML/Graphics.hpp"

# include	"AComponent.hpp"

class		SFMLSpriteComponent : public AComponent<SFMLSpriteComponent>
{
protected:
  sf::Sprite	*_sprite;

public:
		SFMLSpriteComponent(const std::string &filename);
		SFMLSpriteComponent(const SFMLSpriteComponent&);
  virtual	~SFMLSpriteComponent();
  SFMLSpriteComponent	&operator=(const SFMLSpriteComponent&);

  sf::Sprite		*getSprite() const;
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
