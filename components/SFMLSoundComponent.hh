#ifndef SFMLSOUNDCOMPONENT_H_
# define SFMLSOUNDCOMPONENT_H_

# include <string>

# include "ACopyableComponent.hpp"

class SFMLSoundComponent : public ACopyableComponent<SFMLSoundComponent>
{
private:
  bool			_alreadyPlayed;
  std::string		_soundName;
  int			_volume;

public:
  SFMLSoundComponent();
  SFMLSoundComponent(const std::string & fileName);
  virtual ~SFMLSoundComponent();

  const std::string&	getSoundFileName() const;
  int			getVolume() const;
  bool			alreadyPlayed() const;
  void			setPlayed();

  virtual void		serialize(IBuffer &) const;
  virtual void		unserialize(IBuffer &);

  void			deserializeFromFileSpecial(const std::string &lastline,
						   std::ifstream &, unsigned int &lineno);
  void			serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !SFMLSOUNDCOMPONENT_H_ */
