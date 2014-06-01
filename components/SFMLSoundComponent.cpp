
#include "SFMLSoundComponent.hh"

SFMLSoundComponent::SFMLSoundComponent()
  : ACopyableComponent("SFMLSoundComponent"),
    _alreadyPlayed(false), _soundName(""), _volume(100)
{}

SFMLSoundComponent::SFMLSoundComponent(const std::string & fileName)
  : ACopyableComponent("SFMLSoundComponent"),
    _alreadyPlayed(false), _soundName(fileName), _volume(100)
{}

SFMLSoundComponent::~SFMLSoundComponent() {}

const std::string&	SFMLSoundComponent::getSoundFileName() const
{
  return (this->_soundName);
}

int	SFMLSoundComponent::getVolume() const
{
  return (_volume);
}

bool	SFMLSoundComponent::alreadyPlayed() const
{
  return (_alreadyPlayed);
}

void	SFMLSoundComponent::setPlayed()
{
  _alreadyPlayed = true;
}

void SFMLSoundComponent::serialize(IBuffer & buffer) const
{
  buffer << _soundName;
  buffer << _volume;
}

void SFMLSoundComponent::unserialize(IBuffer & buffer)
{
  buffer >> _soundName;
  buffer >> _volume;
}

void	SFMLSoundComponent::deserializeFromFileSpecial(const std::string &lastline,
						       std::ifstream &, unsigned int &lineno)
{
  if (std::regex_match(lastline, std::regex("filename=.+")))
    _soundName = lastline.substr(9);
  else if (std::regex_match(lastline, std::regex("volume=.+")))
    _volume = std::stoi(lastline.substr(7));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	SFMLSoundComponent::serializeFromFile(std::ofstream & output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "filename=" << this->_soundName << std::endl;
}
