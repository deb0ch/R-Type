#include "Unistd.hh"
#include "SoundLoader.hh"
#include <iostream>

SoundLoader::SoundLoader() {
  this->_sounds = std::map<std::string, sf::SoundBuffer *>();
}

SoundLoader::~SoundLoader() {
  auto it = this->_sounds.begin();

  for (it = this->_sounds.begin(); it != this->_sounds.end(); ++it) {
    delete it->second;
  }
}

void SoundLoader::addSound(const std::string &fileSound) {
  auto it = this->_sounds.find(fileSound);

  if (it == this->_sounds.end()) {
    if (access(fileSound.c_str(), R_OK) == -1)
      std::cout << "Exception:: access failed" << std::endl; //TODO throw errno;
    sf::SoundBuffer *buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(fileSound))
      std::cout << "Exception:: loadFromFile failed" << std::endl;; //TODO throw loadFromFile failed
    this->_sounds[fileSound] = buffer;
  }
}

sf::Sound *SoundLoader::getSound(const std::string &fileSound) const {
  auto it = this->_sounds.find(fileSound);

  if (it != this->_sounds.end()) {
    return new sf::Sound(*(it)->second);
  }
  std::cout << "Exception:: file dosent existe" << std::endl;; //TODO throw
  return NULL;
}
