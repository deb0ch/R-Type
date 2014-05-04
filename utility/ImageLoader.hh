#ifndef IMAGELOADER_H_
# define IMAGELOADER_H_

# include <map>
# include "SFML/Graphics.hpp"

class ImageLoader
{
public:
  ImageLoader();
  virtual ~ImageLoader();

public:
  void addImage(const std::string &fileImage);
  sf::Texture *getImage(const std::string &fileImage) const;

private:
  std::map<const std::string, sf::Texture *> _images;

private:
  ImageLoader(const ImageLoader &);
  ImageLoader &operator=(const ImageLoader &);

};

#endif /* !IMAGELOADER_H_ */
