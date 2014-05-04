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
  imageLoader.addImage(this->_filaName, ImageLoader::NbSprite{1,1});

  sf::Sprite *sprite = imageLoader.createSprite(this->_filaName, 0);
  return (sprite);
}
