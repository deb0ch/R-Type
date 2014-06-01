#include "SoundLoader.hh"

SoundLoader::SoundLoader()
{
  _soundBuffers = std::map<std::string, sf::SoundBuffer *>();
  _sounds = std::map<std::string, sf::Sound *>();
}

SoundLoader::~SoundLoader()
{
  for (auto it = _soundBuffers.begin(); it != _soundBuffers.end(); ++it)
    delete it->second;
  for (auto it2 = _sounds.begin(); it2 != _sounds.end(); ++it2)
    delete it2->second;
}

sf::Sound *SoundLoader::getSound(const std::string &fileSound)
{
  auto it = _soundBuffers.find(fileSound);

  if (it != _soundBuffers.end()
      && it->second != NULL)
    {
      if (_sounds.find(fileSound) == _sounds.end())
	_sounds[fileSound] = new sf::Sound(*(it)->second);
      return (_sounds[fileSound]);
    }
  try
    {
      this->addSound(fileSound);
    }
  catch (RTException e)
    {
      std::cerr << e.what() << std::endl;
      return (NULL);
    }
  if (_sounds.find(fileSound) == _sounds.end())
  {
	  _sounds[fileSound] = new sf::Sound(*_soundBuffers.find(fileSound)->second);
	  return (_sounds[fileSound]);
  }
  return (NULL);
}

void SoundLoader::addSound(const std::string &fileSound)
{
  sf::SoundBuffer	*buffer = new sf::SoundBuffer();
  auto			it = _soundBuffers.find(fileSound);

  if (it == _soundBuffers.end())
    {
      if (access((SOUNDFILE + fileSound).c_str(), R_OK) == -1)
	{
	  _soundBuffers[fileSound] = NULL;
	  throw RTException("SoundLoader: file " + fileSound + " does not exist\n");
	}
      if (!buffer->loadFromFile(SOUNDFILE + fileSound))
	{
	  _soundBuffers[fileSound] = NULL;
	  throw RTException("sf::SoundBuffer.loadFromFile failed on file " + fileSound + "\n");
	}
      _soundBuffers[fileSound] = buffer;
    }
}
