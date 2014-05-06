#include	<iostream>

#include	"SFMLRenderSystem.hh"

#include	"SFMLSpriteComponent.hh"
#include	"Pos2DComponent.hh"
#include	"Box2DComponent.hh"

SFMLRenderSystem::SFMLRenderSystem()
  : ASystem("SFMLRenderSystem")
{}

SFMLRenderSystem::~SFMLRenderSystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLRenderSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("SFMLSpriteComponent") &&
      entity->hasComponent("Pos2DComponent") &&
      entity->hasComponent("Box2DComponent"))
    return (true);
  return (false);
}

void		SFMLRenderSystem::processEntity(Entity *entity, const float)
{
  SFMLSpriteComponent	*spriteComp = entity->getComponent<SFMLSpriteComponent>("SFMLSpriteComponent");
  Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  ImageLoader		*imageLoader = this->_world->getSharedObject<ImageLoader>("imageLoader");
  Box2DComponent	*box = entity->getComponent<Box2DComponent>("Box2DComponent");
  float			width, height;

  if (!imageLoader)
    return ; //TODO throw
  width = box->getWidth();
  height = box->getHeight();

  sf::RectangleShape rectangle(sf::Vector2f(width, height));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOrigin(width / 2, height / 2);
  rectangle.setPosition(pos->getX(), pos->getY());
  rectangle.setOutlineThickness(-3);
  rectangle.setOutlineColor(sf::Color(250, 0, 0));
  this->_window->draw(rectangle);

  sf::Sprite *sprite = spriteComp->getSprite(*imageLoader);
  sprite->setPosition(pos->getX() - (width / 2), pos->getY() - (height / 2));
  sprite->setScale(width / sprite->getLocalBounds().width,
		   height / sprite->getLocalBounds().height);
  this->_window->draw(*sprite);
  delete sprite;
}

void		SFMLRenderSystem::start()
{
  this->_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "EpicGradius");
  this->_window->setFramerateLimit(60);
}

void		SFMLRenderSystem::beforeProcess()
{
  this->_window->clear();
}

void		SFMLRenderSystem::afterProcess()
{
  this->_window->display();
}
