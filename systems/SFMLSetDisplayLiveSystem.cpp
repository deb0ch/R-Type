#include "PlayerLifeSystem.hh"
#include "TagComponent.hh"
#include "SFML/Graphics.hpp"
#include "SFMLTextComponent.hh"
#include "SFMLSetDisplayLiveSystem.hh"

SFMLSetDisplayLiveSystem::SFMLSetDisplayLiveSystem()
  : ASystem("SFMLSetDisplayLiveSystem")
{
}

SFMLSetDisplayLiveSystem::~SFMLSetDisplayLiveSystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLSetDisplayLiveSystem::canProcess(Entity *entity) const
{
  TagComponent	*tag = entity->getComponent<TagComponent>("TagComponent");

  if (entity->hasComponent("SFMLTextComponent") && tag && tag->hasTag("render_live"))
    return (true);
  return (false);
}

void		SFMLSetDisplayLiveSystem::processEntity(Entity *entity, const float)
{
  SFMLTextComponent	*sfText = entity->getComponent<SFMLTextComponent>("SFMLTextComponent");
  PlayerLifeSystem	*life = this->_world->getSystem<PlayerLifeSystem>("PlayerLifeSystem");

  if (life) {
    sfText->setText("Life: " + std::to_string(life->getNbLives()));
  }
}
