#include <iostream>
#include "SFMLSpriteComponent.hh"

//----- ----- Constructors ----- ----- //

SFMLSpriteComponent::SFMLSpriteComponent()
	: AComponent("SFMLSpriteComponent")
{
}

SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename, const ImageLoader::NbSprite& sprites,
	const std::map<std::string, std::pair<int, int> > &map, unsigned int tickChange)
	: AComponent("SFMLSpriteComponent")
{
	this->_fileName = filename;
	this->_sprites = sprites;
	this->_tickChange = tickChange;
	this->_counter = 0;
	this->_tickCounter = 0;
	this->_map = map;
	this->_previousAction = "";
}

//----- ----- Destructor ----- ----- //
SFMLSpriteComponent::~SFMLSpriteComponent()
{}

//----- ----- Getters ----- ----- //
sf::Sprite	*SFMLSpriteComponent::getSprite(ImageLoader &imageLoader, const std::string &action)
{
	imageLoader.addImage(this->_fileName, this->_sprites);

	auto it = this->_map.find(action);

	if (it == this->_map.end())
	{
		if (action == "")
			return (NULL);
		it = this->_map.find("");
		if (it == this->_map.end())
			return (NULL);
	}
	if (this->_previousAction == action)
		++this->_tickCounter;
	else
	{
		this->_previousAction = action;
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
	sf::Sprite *sprite = imageLoader.createSprite(this->_fileName,
		this->_counter + it->second.first);
	return (sprite);
}

void		SFMLSpriteComponent::serialize(IBuffer &buffer) const
{
	buffer << this->_fileName;
}

void		SFMLSpriteComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_fileName;
}
