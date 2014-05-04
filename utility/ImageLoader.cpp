#include "ImageLoader.hh"

#include <stdlib.h>
#include <io.h>
#include <process.h>
#include <direct.h>

int fileExists(const std::string & filename)
{
#ifdef _WIN32
	return (_access(filename.c_str(), 4));
#elif __linux__
	return (access(filename.c_str(), 4));
#endif
}

ImageLoader::ImageLoader() {
  this->_images = std::map<std::string, std::pair<sf::Texture *, ImageLoader::InfImg> >();
}

ImageLoader::~ImageLoader() {
  auto it = this->_images.begin();

  for (it = this->_images.begin(); it != this->_images.end(); ++it) {
    delete it->second.first;
  }
}

void ImageLoader::addImage(const std::string &fileImage, ImageLoader::NbSprite nbSprite) {
  auto it = this->_images.find(fileImage);

  if (it == this->_images.end()) {
    sf::Texture	*image = new sf::Texture();

    if (!image->loadFromFile(fileImage))
      throw 4; //TODO throw;
    if (nbSprite.nbSprintX == 0 || nbSprite.nbSprintY == 0)
      throw 5; //TODO throw
    sf::Vector2u v(image->getSize().x / nbSprite.nbSprintX, image->getSize().y / nbSprite.nbSprintY);
    ImageLoader::InfImg infoImg;
    infoImg.nbSprite = nbSprite;
    infoImg.rect = v;
    this->_images[fileImage] = std::pair<sf::Texture *, ImageLoader::InfImg>(image, infoImg);
  }
}

const std::pair<sf::Texture *, ImageLoader::InfImg> &ImageLoader::getPair(const std::string
									  &fileImage) const
{

  auto it = this->_images.find(fileImage);

  if (it != this->_images.end()) {
    return ((it->second));
  }
  throw 5;  //TODO throw
}

sf::Sprite *ImageLoader::createSprite(const std::string &fileImage,
				      const unsigned int  numSprite) const {
  sf::Sprite *sprite = new sf::Sprite();
  //TODO try catch
  auto _pair = this->getPair(fileImage);

  sprite->setTexture(*_pair.first);
  int x = (numSprite % _pair.second.nbSprite.nbSprintX) * _pair.second.rect.x;
  int y = (numSprite / _pair.second.nbSprite.nbSprintX) * _pair.second.rect.y;
  sprite->setTextureRect(sf::IntRect(x, y, _pair.second.rect.x, _pair.second.rect.y));
  return (sprite);
}
