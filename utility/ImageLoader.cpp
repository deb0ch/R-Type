#include "ImageLoader.hh"

ImageLoader::ImageLoader() {
  this->_images = std::map<const std::string, sf::Texture *>();
}

ImageLoader::~ImageLoader() {
  auto it = this->_images.begin();

  for (it = this->_images.begin(); it != this->_images.end(); ++it) {
    delete it->second;
  }
}

void ImageLoader::addImage(const std::string &fileImage) {
  auto it = this->_images.find(fileImage);

  if (it == this->_images.end()) {
    sf::Texture	*image = new sf::Texture();

    if (!image->loadFromFile(fileImage))
      return; //TODO throw;
    this->_images[fileImage] = image;
  }
}

const sf::Texture *ImageLoader::getImage(const std::string &fileImage) const {
  auto it = this->_images.find(fileImage);

  if (it != this->_images.end()) {
    return (it->second);
  }
  return NULL;
}
