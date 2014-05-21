#include	<iostream>

#include	"SFMLRenderSystem.hh"

#include	"SFMLSpriteComponent.hh"
#include	"Pos2DComponent.hh"
#include	"ActionComponent.hh"

SFMLRenderSystem::SFMLRenderSystem()
: ASystem("SFMLRenderSystem")
{}

SFMLRenderSystem::~SFMLRenderSystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLRenderSystem::canProcess(Entity *entity)
{
	if (entity->hasComponent("SFMLSpriteComponent") && entity->hasComponent("Pos2DComponent"))
		return (true);
	return (false);
}

void		SFMLRenderSystem::processEntity(Entity *entity, const float)
{
	SFMLSpriteComponent	*spriteComp = entity->getComponent<SFMLSpriteComponent>("SFMLSpriteComponent");
	Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
	ActionComponent	*action = entity->getComponent<ActionComponent>("ActionComponent");

	ImageLoader *imageLoader = this->_world->getSharedObject<ImageLoader>("imageLoader");
	if (!imageLoader)
		return; //TODO throw
	sf::Sprite *sprite = NULL;
	if (action != NULL)
	{
		if (action->isActive("UP") && spriteComp->hasAction("UP"))
			sprite = spriteComp->getSprite(*imageLoader, "UP");
		else if (action->isActive("DOWN") && spriteComp->hasAction("DOWN"))
			sprite = spriteComp->getSprite(*imageLoader, "DOWN");
	}
	if (sprite == NULL) // default sprite
		sprite = spriteComp->getSprite(*imageLoader);
	if (sprite == NULL)
		return;
	sprite->setPosition(pos->getX(), pos->getY());
	this->_window->draw(*sprite);
	delete sprite;
}

void		SFMLRenderSystem::start()
{
	this->_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "EpicGradius");
	this->_window->setFramerateLimit(60);
	this->_world->setSharedObject("sfmlwindow", this->_window);
}

void		SFMLRenderSystem::beforeProcess()
{
	this->_window->clear();
}

void		SFMLRenderSystem::afterProcess()
{
	this->_window->display();
}
