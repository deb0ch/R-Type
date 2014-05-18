#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include "SFML/Graphics.hpp"
# include "AComponent.hpp"
# include "ImageLoader.hh"
# include "ISerializableComponent.hh"
# include "INetworkSerializableComponent.hh"

class		SFMLSpriteComponent : public AComponent<SFMLSpriteComponent>, public INetworkSerializableComponent
{
protected:
  std::string	_filaName;
  ImageLoader::NbSprite _sprites;

public:
	SFMLSpriteComponent(const std::string &filename = "", ImageLoader::NbSprite = { 5, 5 });
  virtual	~SFMLSpriteComponent();

  virtual	void serialize(IBuffer &buffer) const;
  virtual	void unserialize(IBuffer &buffer);

  sf::Sprite	*getSprite(ImageLoader &imageLoader);
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
