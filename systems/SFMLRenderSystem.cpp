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

  sprite->getSprite()->SetX(pos->getX());
  sprite->getSprite()->SetY(pos->getY());
  this->_window->Draw(*sprite->getSprite());
}

void		SFMLRenderSystem::start()
{
  this->_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "EpicGradius");
}

void		SFMLRenderSystem::beforeProcess()
{
  this->_window->Clear();
}

void		SFMLRenderSystem::afterProcess()
{
  this->_window->Display();
}
