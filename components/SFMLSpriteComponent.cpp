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
sf::Sprite	*SFMLSpriteComponent::getSprite(ImageLoader &imageLoader)
{
  imageLoader.addImage(this->_filaName, ImageLoader::NbSprite{5,5});

  sf::Sprite *sprite = imageLoader.createSprite(this->_filaName, 0);
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
