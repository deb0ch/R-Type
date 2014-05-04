#ifndef IMAGELOADER_H_
# define IMAGELOADER_H_

# include <map>
# include "SFML/Graphics.hpp"

class ImageLoader
{
public:

  typedef struct	s_NbSprite
  {
    unsigned int	nbSprintX;
    unsigned int	nbSprintY;
  }			NbSprite;

  typedef struct	s_InfImg
  {
    NbSprite		nbSprite;
    sf::Vector2u	rect;
  }			InfImg;

public:
  ImageLoader();
  virtual ~ImageLoader();

public:
  void addImage(const std::string &fileImage, ImageLoader::NbSprite nbSprite);
  sf::Sprite *createSprite(const std::string &fileImage, const unsigned int numSprite) const;

private:
  const std::pair<sf::Texture *, ImageLoader::InfImg> &getPair(const std::string &fileImage) const;

private:
  std::map<std::string, std::pair<sf::Texture *, ImageLoader::InfImg> > _images;

private:
  ImageLoader(const ImageLoader &);
  ImageLoader &operator=(const ImageLoader &);

};

#endif /* !IMAGELOADER_H_ */
