#include "SFMLSpriteComponent.hh"

//----- ----- Constructors ----- ----- //
SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename)
  : AComponent("SFMLSpriteComponent")
{
  sf::Image	image;

  image.LoadFromFile(filename);
  this->_sprite = new sf::Sprite(image);
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
