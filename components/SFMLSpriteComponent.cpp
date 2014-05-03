#include "SFMLSpriteComponent.hh"

//----- ----- Constructors ----- ----- //
SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename)
  : AComponent("SFMLSpriteComponent")
{
  sf::Texture	image;

  image.loadFromFile(filename);
  this->_sprite = new sf::Sprite();
  this->_sprite->setTexture(image);
}

SFMLSpriteComponent::SFMLSpriteComponent(const SFMLSpriteComponent &ref)
  : AComponent("SFMLSpriteComponent")
{
  this->_sprite = new sf::Sprite(*ref._sprite);
}

//----- ----- Destructor ----- ----- //
SFMLSpriteComponent::~SFMLSpriteComponent()
{}

//----- ----- Operators ----- ----- //
SFMLSpriteComponent	&SFMLSpriteComponent::operator=(const SFMLSpriteComponent &ref)
{
  this->_sprite = new sf::Sprite(*ref._sprite);
  return (*this);
}

//----- ----- Getters ----- ----- //
sf::Sprite		*SFMLSpriteComponent::getSprite() const
{
  return (this->_sprite);
}

//----- ----- Setters ----- ----- //
