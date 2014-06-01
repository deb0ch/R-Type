#include	<iostream>

#include	"MovementLimitFrame2DSystem.hh"
#include	"MovementLimitFrame2DComponent.hh"
#include	"Pos2DComponent.hh"
#include	"Box2DComponent.hh"

//----- ----- Constructors ----- ----- //
MovementLimitFrame2DSystem::MovementLimitFrame2DSystem()
  : ASystem("MovementLimitFrame2DSystem")
{}

//----- ----- Destructor ----- ----- //
MovementLimitFrame2DSystem::~MovementLimitFrame2DSystem()
{}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
//----- ----- Methods ----- ----- //
bool		MovementLimitFrame2DSystem::canProcess(Entity *e) const
{
  if (e->hasComponent("MovementLimitFrame2DComponent")
      && e->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void	MovementLimitFrame2DSystem::processEntity(Entity *e, const float)
{
  MovementLimitFrame2DComponent*	frame;
  Pos2DComponent*			pos;
  Box2DComponent*			box;
  float					width = 0;
  float					height = 0;

  if (!(frame = e->getComponent<MovementLimitFrame2DComponent>("MovementLimitFrame2DComponent"))
      || !(pos = e->getComponent<Pos2DComponent>("Pos2DComponent")))
    return ;
  if ((box = e->getComponent<Box2DComponent>("Box2DComponent")))
    {
      width = box->getWidth();
      height = box->getHeight();
    }
  if (pos->getX() < frame->getPosX() + (width / 2.f))
    pos->setX(frame->getPosX() + (width / 2.f));
  if (pos->getX() > frame->getPosX() + frame->getWidth() - (width / 2.f))
    pos->setX(frame->getPosX() + frame->getWidth() - (width / 2.f));
  if (pos->getY() < frame->getPosY() + (height / 2.f))
    pos->setY(frame->getPosY() + (height / 2.f));
  if (pos->getY() > frame->getPosY() + frame->getHeight() - (height / 2.f))
    pos->setY(frame->getPosY() + frame->getHeight() - (height / 2.f));
}
