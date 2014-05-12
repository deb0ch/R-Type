#include	<iostream>

#include	"SFMLRenderSystem.hh"

#include	"SFMLSpriteComponent.hh"
#include	"Pos2DComponent.hh"

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

  ImageLoader *imageLoader = this->_world->getSharedObject<ImageLoader>("imageLoader");
  if (!imageLoader)
    return ; //TODO throw
  sf::Sprite *sprite = spriteComp->getSprite(*imageLoader);
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
