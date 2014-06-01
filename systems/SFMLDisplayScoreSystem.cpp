#include <iostream>

#include "ScoreSystem.hh"
#include "TagComponent.hh"
#include "SFML/Graphics.hpp"
#include "SFMLTextComponent.hh"
#include "SFMLDisplayScoreSystem.hh"

SFMLDisplayScoreSystem::SFMLDisplayScoreSystem()
  : ASystem("SFMLDisplayScoreSystem")
{
}

SFMLDisplayScoreSystem::~SFMLDisplayScoreSystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLDisplayScoreSystem::canProcess(Entity *entity)
{
  TagComponent	*tag = entity->getComponent<TagComponent>("TagComponent");

  if (entity->hasComponent("SFMLTextComponent") && tag && tag->hasTag("render_score"))
    return (true);
  return (false);
}

void		SFMLDisplayScoreSystem::processEntity(Entity *entity, const float)
{
  SFMLTextComponent	*sfText = entity->getComponent<SFMLTextComponent>("SFMLTextComponent");
  ScoreSystem		*score = this->_world->getSystem<ScoreSystem>("ScoreSystem");

  if (score) {
    sfText->setText("Score: " + std::to_string(score->getScore()));
  }
}
