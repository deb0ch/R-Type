#include	"SFMLRenderSystem.hh"
#include	"SFMLSpriteComponent.hh"
#include	"CollisionComponent.hh"
#include	"ActionComponent.hh"
#include	"RTException.hh"

SFMLRenderSystem::SFMLRenderSystem()
  : ASystem("SFMLRenderSystem")
{}

SFMLRenderSystem::~SFMLRenderSystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLRenderSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("SFMLSpriteComponent") && entity->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void		SFMLRenderSystem::displayCollision(Entity *entity, sf::RenderWindow *_window)
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
      _window->draw(rectangle);
    }
}

void		SFMLRenderSystem::displayBox2D(float width, float height, Pos2DComponent *pos, sf::RenderWindow *_window)
{
  sf::RectangleShape rectangle(sf::Vector2f(width, height));

  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOrigin(width / 2, height / 2);
  rectangle.setPosition(pos->getX(), pos->getY());
  rectangle.setOutlineThickness(-3);
  rectangle.setOutlineColor(sf::Color(250, 0, 0));
  _window->draw(rectangle);
}

void		SFMLRenderSystem::processEntity(Entity *entity, const float)
{
  SFMLSpriteComponent	*spriteComp = entity->getComponent<SFMLSpriteComponent>("SFMLSpriteComponent");
  Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  Box2DComponent	*box = entity->getComponent<Box2DComponent>("Box2DComponent");
  ActionComponent	*action = entity->getComponent<ActionComponent>("ActionComponent");
  float			width;
  float			height;
  ImageLoader		*imageLoader = this->_world->getSharedObject<ImageLoader>("imageLoader");
  sf::RenderWindow	*_window = this->_world->getSharedObject<sf::RenderWindow>("sfmlwindow");

  if (!imageLoader)
    throw RTException("The world does not contain ImageLoader");

  sf::Sprite *sprite = NULL;

  if (action != NULL)
    {
      if (action->isActive("UP") && spriteComp->hasAction("UP"))
	sprite = this->getSprite(*imageLoader, spriteComp, "UP");
      else if (action->isActive("DOWN") && spriteComp->hasAction("DOWN"))
	sprite = this->getSprite(*imageLoader, spriteComp, "DOWN");
    }
  width = (box) ? box->getWidth() : 0;
  height = (box) ? box->getHeight() : 0;
  if (World::DEBUG)
    {
      displayBox2D(width, height, pos, _window);
      if (entity->hasComponent("CollisionComponent"))
	displayCollision(entity, _window);
    }
  if (sprite == NULL)
    sprite = this->getSprite(*imageLoader, spriteComp, "");
  if (sprite == NULL)
    {
      return;
    }
  sprite->setPosition(pos->getX() - (width / 2), pos->getY() - (height / 2));
  if (box)
    sprite->setScale(width / sprite->getLocalBounds().width,
		     height / sprite->getLocalBounds().height);
  _window->draw(*sprite);
  delete sprite;
}

void		SFMLRenderSystem::start()
{}

void		SFMLRenderSystem::beforeProcess(const float)
{}

void		SFMLRenderSystem::afterProcess(const float)
{}

sf::Sprite	*SFMLRenderSystem::getSprite(ImageLoader &imageLoader, SFMLSpriteComponent *component,
					     const std::string &action)
{
  imageLoader.addImage(component->getFileName(), component->getSpriteDim());
  return imageLoader.createSprite(component->getFileName(),
				  component->getCurrentSpriteNumber(action));
}
