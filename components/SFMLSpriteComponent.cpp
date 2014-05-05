#include <iostream>
#include "SFMLSpriteComponent.hh"
#include "Serializer.hpp"

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

int		SFMLSpriteComponent::serialize(char *buffer, int lenght) const
{
  int		lenght_written;

  lenght_written = 0;
  lenght_written += Serializer<std::string>::serialize(buffer + lenght_written,
						       lenght - lenght_written, this->_filaName);
  std::cout << "Serializing: " << this->_filaName << " : " << buffer << std::endl;
  return (lenght_written);
}

int		SFMLSpriteComponent::unserialize(const char *buffer, int lenght)
{
  int		lenght_read;

  lenght_read = 0;
  lenght_read += Serializer<std::string>::unserialize(buffer + lenght_read,
						      lenght - lenght_read, this->_filaName);
  std::cout << "Unserializing pozkepoaepkazoepoaze: " << this->_filaName << " : " << buffer << std::endl;
  return (lenght_read);
}
