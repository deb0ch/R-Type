#ifndef SFMLSOUNDSYSTEM_H_
# define SFMLSOUNDSYSTEM_H_

# include "SFML/Graphics.hpp"

# include "ASystem.hh"
# include "SFMLSoundComponent.hh"
# include "SoundLoader.hh"

class SFMLSoundSystem : public ASystem
{
public:
  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float);

public:
			SFMLSoundSystem();
  virtual		~SFMLSoundSystem();

  virtual void		start();

protected:
  SoundLoader		*_soundLoader;
};

#endif /* !SFMLSOUNDSYSTEM_H_ */
