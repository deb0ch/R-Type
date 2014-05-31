#include <iostream>
#include "SFMLSpriteComponent.hh"

//----- ----- Constructors ----- ----- //

SFMLSpriteComponent::SFMLSpriteComponent()
: ACopyableComponent("SFMLSpriteComponent")
{
  this->_currentSprite = 0;
  this->_sprites.first = 0;
  this->_sprites.second = 0;
  this->_fileName = "";
  this->_tickCounter = 0;
  this->_counter = 0;
}

SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename, const std::pair<int, int>& sprites,
					 const std::map<std::string, std::pair<int, int> > &map, unsigned int tickChange)
  : ACopyableComponent("SFMLSpriteComponent")
{
  this->_fileName = filename;
  this->_sprites = sprites;
  this->_tickChange = tickChange;
  this->_counter = 0;
  this->_tickCounter = 0;
  this->_currentSprite = 0;
  this->_map = map;
  this->_previousAction = "";
}

//----- ----- Destructor ----- ----- //
SFMLSpriteComponent::~SFMLSpriteComponent()
{}

bool		SFMLSpriteComponent::hasAction(const std::string & action)
{
  auto it = this->_map.find(action);
  if (it == this->_map.end())
    return (false);
  return (true);
}

const std::string	&SFMLSpriteComponent::getFileName() const
{
  return this->_fileName;
}

const std::pair<int, int> &SFMLSpriteComponent::getSpriteDim() const
{
  return this->_sprites;
}

int			SFMLSpriteComponent::getCurrentSpriteNumber(const std::string &action)
{
  auto it = this->_map.find(action);

  if (it == this->_map.end())
    {
      if (action == "")
	return (-1);
      it = this->_map.find("");
      if (it == this->_map.end())
	return (-1);
    }
  if (this->_previousAction == it->first)
    ++this->_tickCounter;
  else
    {
      this->_previousAction = it->first;
      this->_tickCounter = 0;
      this->_counter = 0;
    }
  if (this->_tickCounter > this->_tickChange)
    {
      ++(this->_counter);
      if (this->_counter >= it->second.second)
	this->_counter = 0;
      this->_tickCounter = 0;
    }
  return (this->_counter + it->second.first);
}

void		SFMLSpriteComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_fileName;
  buffer << this->_sprites.first;
  buffer << this->_sprites.second;
  buffer << this->_tickChange;
  buffer << static_cast<unsigned int>(this->_map.size());
  std::for_each(this->_map.begin(), this->_map.end(),
		[&buffer] (const std::pair< std::string, std::pair<int, int> > &pair)
		{
		  buffer << pair.first;
		  buffer << pair.second.first;
		  buffer << pair.second.second;
		});
}

void		SFMLSpriteComponent::unserialize(IBuffer &buffer)
{
  unsigned int	nb_elem;
  std::string	tmp;
  std::pair<int, int> pair;

  buffer >> this->_fileName;
  buffer >> this->_sprites.first;
  buffer >> this->_sprites.second;
  buffer >> this->_tickChange;
  buffer >> nb_elem;
  this->_map.clear();
  for(unsigned int i = 0; i < nb_elem; ++i)
    {
      buffer >> tmp;
      buffer >> pair.first;
      buffer >> pair.second;
      this->_map[tmp] = pair;
    }
}

void	SFMLSpriteComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input,
							unsigned int &lineno)
{
  if (std::regex_match(lastline, std::regex("filename=.+")))
    this->_fileName = lastline.substr(9);
  else if (std::regex_match(lastline, std::regex("nbSpritesX=.+")))
    this->_sprites.first = std::stoi(lastline.substr(11));
  else if (std::regex_match(lastline, std::regex("nbSpritesY=.+")))
    this->_sprites.second = std::stoi(lastline.substr(11));
  else if (std::regex_match(lastline, std::regex("tickChange=.+")))
    this->_tickChange = std::stoi(lastline.substr(11));
  else if (std::regex_match(lastline, std::regex("anim=ANIM")))
    {
      std::string		line;
      std::string		action;
      std::pair<int, int>	pair;
      while (std::getline(input, line))
	{
	  ++lineno;
	  line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
	  if (std::regex_match(line, std::regex("action=.*")))
	    action = line.substr(7);
	  else if (std::regex_match(line, std::regex("start=.+")))
	    pair.first = std::stoi(line.substr(6));
	  else if (std::regex_match(line, std::regex("length=.+")))
	    pair.second = std::stoi(line.substr(7));
	  else if (std::regex_match(line, std::regex("!ANIM")))
	    {
	      this->_map[action] = pair;
	      break ;
	    }
	  else
	    throw EntityFileException("Bad argument for ANIM : \"" + line + "\"", lineno);
	}
    }
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void		SFMLSpriteComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "filename=" << this->_fileName << std::endl;
  output << std::string(indent, '\t') << "nbSpritesX=" << this->_sprites.first << std::endl;
  output << std::string(indent, '\t') << "nbSpritesY=" << this->_sprites.second << std::endl;
  output << std::string(indent, '\t') << "tickChange=" << this->_tickChange << std::endl;
  std::for_each(this->_map.begin(), this->_map.end(), [&output, indent](const std::pair<std::string, std::pair<int, int> > &pair) {
      output << std::string(indent, '\t') << "anim=ANIM" << std::endl;
      output << std::string(indent + 1, '\t') << "action=" << pair.first << std::endl;
      output << std::string(indent + 1, '\t') << "start=" << pair.second.first << std::endl;
      output << std::string(indent + 1, '\t') << "length="<< pair.second.second << std::endl;
      output << std::string(indent, '\t') << "!ANIM" << std::endl;
    });
}






















/*

sf::Sprite	*SFMLSpriteComponent::getSpriteFromMap(ImageLoader &imageLoader, const std::string &action)
{
	auto it = this->_map.find(action);

	if (it == this->_map.end())
	{
		if (action == "")
			return (NULL);
		it = this->_map.find("");
		if (it == this->_map.end())
			return (NULL);

	}
	if (this->_previousAction == it->first)
		++this->_tickCounter;
	else
	{
		this->_previousAction = it->first;
		this->_tickCounter = 0;
		this->_counter = 0;
	}
	if (this->_tickCounter > this->_tickChange)
	{
		++(this->_counter);
		if (this->_counter >= it->second.second)
			this->_counter = 0;
		this->_tickCounter = 0;
	}
	this->_currentSprite = this->_counter + it->second.first;
	sf::Sprite *sprite = imageLoader.createSprite(this->_fileName, this->_currentSprite);
	return (sprite);
}

sf::Sprite	*SFMLSpriteComponent::getSpriteWithoutMap(ImageLoader &imageLoader, const std::string &)
{
  ++this->_tickCounter;
  if (this->_tickCounter > this->_tickChange)
    {
      ++(this->_counter);
      if (this->_counter >= this->_nbSprite)
	this->_counter = 0;
      this->_tickCounter = 0;
    }
  this->_currentSprite = this->_counter + this->_first;
  sf::Sprite *sprite = imageLoader.createSprite(this->_fileName, this->_currentSprite);
  return (sprite);
}

//----- ----- Getters ----- ----- //
sf::Sprite	*SFMLSpriteComponent::getSprite(ImageLoader &imageLoader, const std::string &action)
{
	imageLoader.addImage(this->_fileName, this->_sprites);

	if (this->_mapexist)
		return (this->getSpriteFromMap(imageLoader, action));
	else
		return (this->getSpriteWithoutMap(imageLoader, action));
}
*/
