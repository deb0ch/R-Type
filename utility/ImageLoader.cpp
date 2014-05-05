#include "Unistd.hh"
#include "RTException.hh"
#include "ImageLoader.hh"

static std::string NAME_CLASS = "RT::ImageLoader";

ImageLoader::ImageLoader() {
  this->_images = std::map<std::string, std::pair<sf::Texture *, ImageLoader::InfImg> >();
  RTException::addClass(NAME_CLASS, "Execption ImageLoader");
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

    if (access(fileImage.c_str(), R_OK) == -1)
      throw RTException(NAME_CLASS, errno, RTException::S_ERROR);
    if (!image->loadFromFile(fileImage))
      throw RTException(NAME_CLASS, "loadFromFile failed", RTException::S_ERROR);
    if (nbSprite.nbSprintX == 0 || nbSprite.nbSprintY == 0)
      throw RTException(NAME_CLASS, "Invalide ImageLoader::NbSprite", RTException::S_ERROR);
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
  throw RTException(NAME_CLASS, "Invalide ImageLoader::NbSprite", RTException::S_WARNING);
}

sf::Sprite *ImageLoader::createSprite(const std::string &fileImage,
				      const unsigned int  numSprite) const {
  sf::Sprite *sprite = new sf::Sprite();
  std::pair<sf::Texture *, ImageLoader::InfImg> textureInfo;

  try {
    textureInfo = this->getPair(fileImage);
  } catch (RTException e) {
    throw RTException(NAME_CLASS, e.what(), RTException::S_ERROR);
  }
  sprite->setTexture(*textureInfo.first);
  int x = (numSprite % textureInfo.second.nbSprite.nbSprintX) * textureInfo.second.rect.x;
  int y = (numSprite / textureInfo.second.nbSprite.nbSprintX) * textureInfo.second.rect.y;
  sprite->setTextureRect(sf::IntRect(x, y, textureInfo.second.rect.x, textureInfo.second.rect.y));
  return (sprite);
}
