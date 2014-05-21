#include	<iostream>
#include	<list>

#include	"SFMLRenderSystem.hh"

#include	"SFMLSpriteComponent.hh"
#include	"CollisionComponent.hh"
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

void		SFMLRenderSystem::displayCollision(Entity *entity)
{
  std::list<CollisionPoint *>	const &entityPoints = entity->getComponent<CollisionComponent>("CollisionComponent")->getCollisionPoints();
  Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  Pos2DComponent	*posC;
  Box2DComponent	*boxC;

  for (auto it = entityPoints.begin(); it != entityPoints.end(); ++it)
    {
      posC = (*it)->getPos();
      boxC = (*it)->getBox();
      float	width = boxC->getWidth();
      float	height = boxC->getHeight();
      sf::RectangleShape rectangle(sf::Vector2f(width, height));
      rectangle.setFillColor(sf::Color::Transparent);
      rectangle.setPosition(pos->getX() + posC->getX(), pos->getY() + posC->getY());
      rectangle.setOrigin(width / 2, height / 2);
      rectangle.setOutlineThickness(-3);
      rectangle.setOutlineColor(sf::Color(0, 250, 0));
      this->_window->draw(rectangle);
    }
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

  /*  display for debug here */
  sf::RectangleShape rectangle(sf::Vector2f(width, height));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOrigin(width / 2, height / 2);
  rectangle.setPosition(pos->getX(), pos->getY());
  rectangle.setOutlineThickness(-3);
  rectangle.setOutlineColor(sf::Color(250, 0, 0));
  this->_window->draw(rectangle);
  displayCollision(entity);
  /*  end of debug display */

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
