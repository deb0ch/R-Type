#include <iostream>
#include "SFMLSpriteComponent.hh"

//----- ----- Constructors ----- ----- //

SFMLSpriteComponent::SFMLSpriteComponent()
: ACopyableComponent("SFMLSpriteComponent")
{
	this->_mapexist = false;
	this->_currentSprite = 0;
	this->_sprites.nbSprintX = 0;
	this->_sprites.nbSprintY = 0;
	this->_fileName = "";
	this->_tickCounter = 0;
	this->_counter = 0;
}

SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename, const ImageLoader::NbSprite& sprites,
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
	this->_mapexist = true;
}

//----- ----- Destructor ----- ----- //
SFMLSpriteComponent::~SFMLSpriteComponent()
{}

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

bool		SFMLSpriteComponent::hasAction(const std::string & action)
{
	auto it = this->_map.find(action);
	if (it == this->_map.end())
		return (false);
	return (true);
}

void		SFMLSpriteComponent::serialize(IBuffer &buffer) const
{
	int	first;
	int	nb_sprites;
	auto it = this->_map.find(this->_previousAction);

	 // DANGEROUS (if you return here, unserialize cannot know it and will try to read more than it has)
	// if (it == this->_map.end())
	// 	return;

	if (it != this->_map.end())
	  {
	    first = it->second.first;
	    nb_sprites = it->second.second;
	  }
	else
	  {
	    first = 0;
	    nb_sprites = 0;
	  }
	buffer << this->_fileName;
	buffer << this->_sprites.nbSprintX;
	buffer << this->_sprites.nbSprintY;
	buffer << this->_tickChange;
	buffer << this->_tickCounter;
	buffer << this->_currentSprite;
	buffer << first;
	buffer << nb_sprites;
}

void		SFMLSpriteComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_fileName;
	buffer >> this->_sprites.nbSprintX;
	buffer >> this->_sprites.nbSprintY;
	buffer >> this->_tickChange;
	buffer >> this->_tickCounter;
	buffer >> this->_currentSprite;
	buffer >> this->_first;
	buffer >> this->_nbSprite;
}

void		SFMLSpriteComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "filename=" << this->_fileName << std::endl;
  output << std::string(indent, '\t') << "nbSpritesX=" << this->_sprites.nbSprintX << std::endl;
  output << std::string(indent, '\t') << "nbSpritesY=" << this->_sprites.nbSprintY << std::endl;
  std::for_each(this->_map.begin(), this->_map.end(), [&output, indent](const std::pair<std::string, std::pair<int, int> > &pair){
      output << std::string(indent, '\t') << "anim=" << pair.first << ";" << pair.second.first << ";" << pair.second.second << std::endl;
    });
}
