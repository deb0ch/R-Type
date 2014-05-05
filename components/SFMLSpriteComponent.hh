#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include "SFML/Graphics.hpp"
# include "AComponent.hpp"
# include "ImageLoader.hh"
# include "ISerializableComponent.hh"

class		SFMLSpriteComponent : public AComponent<SFMLSpriteComponent>, public ISerializableComponent
{
protected:
  std::string	_filaName;

public:
		SFMLSpriteComponent(const std::string &filename = "");
  virtual	~SFMLSpriteComponent();

  virtual	int serialize(char *buffer, int lenght) const;
  virtual	int unserialize(const char *buffer, int lenght);

  sf::Sprite	*getSprite(ImageLoader &imageLoader);
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
