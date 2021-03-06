#include "SFML/Graphics.hpp"
#include "SFMLTextComponent.hh"
#include "SFMLRenderTextSystem.hh"

SFMLRenderTextSystem::SFMLRenderTextSystem()
  : ASystem("SFMLRenderTextSystem")
{
}

SFMLRenderTextSystem::~SFMLRenderTextSystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLRenderTextSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("SFMLTextComponent") && entity->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void		SFMLRenderTextSystem::processEntity(Entity *entity, const float)
{
  SFMLTextComponent	*sfText = entity->getComponent<SFMLTextComponent>("SFMLTextComponent");
  Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  sf::RenderWindow	*renderWindow = this->_world->getSharedObject<sf::RenderWindow>("sfmlwindow");
  sf::Font font;
  sf::Text text;

  if (renderWindow && font.loadFromFile("Ressources/Fonts/gradius.ttf"))
    {
      text.setFont(font);
      text.setString(sfText->getText());
      text.setColor(sf::Color(255, 102, 0));
      text.setCharacterSize(48);
      text.setPosition(pos->getX(), pos->getY());
      renderWindow->draw(text);
    }
}
