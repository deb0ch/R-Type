#include <iostream>
#include "SFMLSpriteComponent.hh"

//----- ----- Constructors ----- ----- //
SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename)
  : AComponent("SFMLSpriteComponent"), _filaName(filename)
{}

//----- ----- Destructor ----- ----- //
SFMLSpriteComponent::~SFMLSpriteComponent()
{}

//----- ----- Getters ----- ----- //
sf::Sprite	*SFMLSpriteComponent::getSprite(ImageLoader &imageLoader) {
  sf::Sprite	*sprite = new sf::Sprite();

  //TODO catch exection
  imageLoader.addImage(this->_filaName);
  sf::Texture *image = imageLoader.getImage(this->_filaName);
  if (!image)
    return NULL;
  sprite->setTexture(*image);
  return (sprite);
}

void		SFMLSpriteComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_filaName;
}

void		SFMLSpriteComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_filaName;
}
