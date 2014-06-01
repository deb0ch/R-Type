
#include "SoundLoader.hh"

SoundLoader::SoundLoader()
{
  _sounds = std::map<std::string, sf::SoundBuffer *>();
}

SoundLoader::~SoundLoader()
{
  auto it = _sounds.begin();

  for (it = _sounds.begin(); it != _sounds.end(); ++it)
    delete it->second;
}

sf::Sound *SoundLoader::getSound(const std::string &fileSound)
{
  auto it = _sounds.find(fileSound);

  if (it != _sounds.end()
      && it->second != NULL)
    return new sf::Sound(*(it)->second);
  else if (it->second == NULL)
    return (NULL);
  try
    {
      this->addSound(fileSound);
    }
  catch (RTException e)
    {
      std::cout << e.what() << std::endl;
      return (NULL);
    }
  return (new sf::Sound(*_sounds.find(fileSound)->second));
}

void SoundLoader::addSound(const std::string &fileSound)
{
  sf::SoundBuffer	*buffer = new sf::SoundBuffer();
  auto			it = _sounds.find(fileSound);

  if (it == _sounds.end())
    {
      if (access((SOUNDFILE + fileSound).c_str(), R_OK) == -1)
	{
	  _sounds[fileSound] = NULL;
	  throw RTException("SoundLoader: file " + fileSound + " does not exist\n");
	}
      if (!buffer->loadFromFile(SOUNDFILE + fileSound))
	{
	  _sounds[fileSound] = NULL;
	  throw RTException("sf::SoundBuffer.loadFromFile failed on file " + fileSound + "\n");
	}
      _sounds[fileSound] = buffer;
    }
}
