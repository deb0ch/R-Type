#ifndef SOUNDLOADER_H_
# define SOUNDLOADER_H_

# include <iostream>
# include <map>
# include "SFML/Audio/Sound.hpp"
# include "SFML/Audio/SoundBuffer.hpp"

# include "RTException.hh"
# include "Unistd.hh"

# define SOUNDFILE "Ressources/Sound/"

class SoundLoader
{
public:
  SoundLoader();
  virtual ~SoundLoader();

public:
  sf::Sound	*getSound(const std::string &fileSound);

private:
  SoundLoader(const SoundLoader &);
  SoundLoader &operator=(const SoundLoader &);

private:
  void		addSound(const std::string &fileSound);

private:
  std::map<std::string, sf::SoundBuffer *> _soundBuffers;
  std::map<std::string, sf::Sound *> _sounds;
};

#endif /* !SOUNDLOADER_H_ */
