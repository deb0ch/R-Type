#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include "SFML/Graphics.hpp"
# include "ImageLoader.hh"
# include "ACopyableComponent.hpp"

class		SFMLSpriteComponent : public ACopyableComponent<SFMLSpriteComponent>
{
protected:
  std::string	_filaName;

public:
		SFMLSpriteComponent(const std::string &filename = "");
  virtual	~SFMLSpriteComponent();

  virtual	void serialize(IBuffer &buffer) const;
  virtual	void unserialize(IBuffer &buffer);

  sf::Sprite	*getSprite(ImageLoader &imageLoader);
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
