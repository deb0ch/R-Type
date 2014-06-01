
#include "SFMLSoundSystem.hh"

SFMLSoundSystem::SFMLSoundSystem()
  : ASystem("SFMLSoundSystem")
{}

SFMLSoundSystem::~SFMLSoundSystem()
{}

bool	SFMLSoundSystem::canProcess(Entity *e)
{
  if (e->hasComponent("SFMLSoundComponent"))
    return (true);
  return (false);
}

void	SFMLSoundSystem::processEntity(Entity * e, const float)
{
  SFMLSoundComponent	*sound;

  sound = e->getComponent<SFMLSoundComponent>("SFMLSoundComponent");

  if (!sound)
    return ;
  if (!sound->alreadyPlayed())
    {
      sf::Sound *sfSound = _soundLoader->getSound(sound->getSoundFileName());

      if (sfSound)
	sfSound->play();
      sound->setPlayed();
    }
}

void	SFMLSoundSystem::start()
{
  if (!(_soundLoader = _world->getSharedObject<SoundLoader>("soundLoader")))
    {
      _soundLoader = new SoundLoader();
      _world->setSharedObject("soundLoader", _soundLoader);
    }
}
