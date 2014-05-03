#include	<iostream>

#include	"SFMLRenderSystem.hh"

#include	"SFMLSpriteComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
SFMLRenderSystem::SFMLRenderSystem()
  : ASystem("SFMLRenderSystem")
{}

//----- ----- Destructor ----- ----- //
SFMLRenderSystem::~SFMLRenderSystem()
{}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
//----- ----- Methods ----- ----- //
bool		SFMLRenderSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("SFMLSpriteComponent") && entity->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void		SFMLRenderSystem::processEntity(Entity *entity, const float)
{
  SFMLSpriteComponent	*sprite = entity->getComponent<SFMLSpriteComponent>("SFMLSpriteComponent");
  Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");

  sprite->getSprite()->setPosition(pos->getX(), pos->getY());
  this->_window->draw(*sprite->getSprite());
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
