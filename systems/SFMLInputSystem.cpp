#include	<map>

#include	"SFMLInputSystem.hh"
#include	"SFMLInputComponent.hh"
#include	"SFMLKeyEvent.hh"
#include	"ActionComponent.hh"

SFMLInputSystem::SFMLInputSystem()
  : ASystem("SFMLInputSystem")
{}

SFMLInputSystem::~SFMLInputSystem()
{}

void	SFMLInputSystem::SFMLKeyEventListener(IEvent * ievent)
{
  SFMLKeyEvent*		event = dynamic_cast<SFMLKeyEvent*>(ievent);

  if (!event)
    return ;

  this->_inputs[event->_key] = event->_active;
}

void	SFMLInputSystem::init()
{
  this->_world->addEventHandler("SFMLKeyEvent", this, &SFMLInputSystem::SFMLKeyEventListener);
}

bool	SFMLInputSystem::canProcess(Entity *e) {
  if (e->hasComponent("SFMLInputComponent") && e->hasComponent("ActionComponent"))
    return (true);
  return (false);
}

void	SFMLInputSystem::processEntity(Entity *e, const float)
{
  SFMLInputComponent	*inputComp;
  ActionComponent	*actionComp;
  bool			tmp;

  inputComp = e->getComponent<SFMLInputComponent>("SFMLInputComponent");
  actionComp = e->getComponent<ActionComponent>("ActionComponent");
  for (auto it = inputComp->getInputs().begin() ; it != inputComp->getInputs().end() ; ++it)
    {
      tmp = false;
      for (auto it2 = it->second.begin() ; it2 != it->second.end() ; ++it2)
	tmp |= this->_inputs[*it2];
      actionComp->setAction(it->first, tmp);
    }
}
