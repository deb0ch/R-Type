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

  virtual	void serialize(IBuffer &buffer) const;
  virtual	void unserialize(IBuffer &buffer);

  sf::Sprite	*getSprite(ImageLoader &imageLoader);
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
