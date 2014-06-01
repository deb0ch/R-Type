
#include "SFMLSoundComponent.hh"

SFMLSoundComponent::SFMLSoundComponent()
  : ACopyableComponent("SFMLSoundComponent"), _alreadyPlayed(false), _soundName("")
{}

SFMLSoundComponent::SFMLSoundComponent(const std::string & fileName)
  : ACopyableComponent("SFMLSoundComponent"), _alreadyPlayed(false), _soundName(fileName)
{}

SFMLSoundComponent::~SFMLSoundComponent() {}

const std::string&	SFMLSoundComponent::getSoundFileName() const
{
  return (this->_soundName);
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
}

void SFMLSoundComponent::unserialize(IBuffer & buffer)
{
  buffer >> _soundName;
}

void	SFMLSoundComponent::deserializeFromFileSpecial(const std::string &lastline,
						       std::ifstream &, unsigned int &lineno)
{
  if (std::regex_match(lastline, std::regex("filename=.+")))
    _soundName = lastline.substr(9);
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	SFMLSoundComponent::serializeFromFile(std::ofstream & output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "filename=" << this->_soundName << std::endl;
}
