#ifndef SOUNDLOADER_H_
# define SOUNDLOADER_H_

# include <map>
# include "SFML/Audio/Sound.hpp"
# include "SFML/Audio/SoundBuffer.hpp"

class SoundLoader
{
public:
  SoundLoader();
  virtual ~SoundLoader();

public:
  void addSound(const std::string &fileSound);
  sf::Sound *getSound(const std::string &fileSound) const;

private:
  std::map<std::string, sf::SoundBuffer *> _sounds;

private:
  SoundLoader(const SoundLoader &);
  SoundLoader &operator=(const SoundLoader &);

};


#endif /* !SOUNDLOADER_H_ */
