#include <iostream>
#include "SFMLSpriteComponent.hh"

//----- ----- Constructors ----- ----- //
SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename, ImageLoader::NbSprite sprites,
	int nbSprites, int firstSprite, unsigned int tickChange)
	: AComponent("SFMLSpriteComponent"), _filaName(filename)
{
	this->_sprites = sprites;
	this->_nbSprites = nbSprites;
	this->_counter = 0;
	this->_tickChange = tickChange;
	this->_tickCounter = 0;
	this->_firstSprite = firstSprite;
}

//----- ----- Destructor ----- ----- //
SFMLSpriteComponent::~SFMLSpriteComponent()
{}

//----- ----- Getters ----- ----- //
sf::Sprite	*SFMLSpriteComponent::getSprite(ImageLoader &imageLoader)
{
	imageLoader.addImage(this->_filaName, this->_sprites);

	++this->_tickCounter;
	if (this->_tickCounter > this->_tickChange)
	{
		++(this->_counter);
		if (_counter >= this->_nbSprites)
			this->_counter = 0;
		this->_tickCounter = 0;
	}
	sf::Sprite *sprite = imageLoader.createSprite(this->_filaName, this->_counter + this->_firstSprite);
	return (sprite);
}

void		SFMLSpriteComponent::serialize(IBuffer &buffer) const
{
	buffer << this->_filaName;
}

void		SFMLSpriteComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_filaName;
}
