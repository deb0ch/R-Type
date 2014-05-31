#include	<map>

#include	"SFMLInputSystem.hh"
#include	"SFMLInputComponent.hh"
#include	"SFMLJoystickComponent.hh"
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

void	SFMLInputSystem::SFMLJoystickEventListener(IEvent * ievent)
{
  SFMLJoystickEvent*	event = dynamic_cast<SFMLJoystickEvent*>(ievent);

  if (!event)
    return ;

  this->_inputsJoystick[event->_key] = event->_active;
}

void	SFMLInputSystem::init()
{
  this->_world->addEventHandler("SFMLKeyEvent", this, &SFMLInputSystem::SFMLKeyEventListener);
  this->_world->addEventHandler("SFMLJoystickEvent", this, &SFMLInputSystem::SFMLJoystickEventListener);
}

bool	SFMLInputSystem::canProcess(Entity *e) {
  if (e->hasComponent("ActionComponent"))
    return (true);
  return (false);
}

void	SFMLInputSystem::processEntity(Entity *e, const float)
{
  SFMLInputComponent	*inputComp;
  SFMLJoystickComponent	*joystickComp;
  ActionComponent	*actionComp;

  std::map<std::string, bool>	actionstmp;

  inputComp = e->getComponent<SFMLInputComponent>("SFMLInputComponent");
  joystickComp = e->getComponent<SFMLJoystickComponent>("SFMLJoystickComponent");
  actionComp = e->getComponent<ActionComponent>("ActionComponent");

  if (inputComp)
    for (auto it = inputComp->getInputs().begin() ; it != inputComp->getInputs().end() ; ++it)
      for (auto it2 = it->second.begin() ; it2 != it->second.end() ; ++it2)
	actionstmp[it->first] |= this->_inputs[*it2];

  if (joystickComp)
    for (auto it = joystickComp->getInputs().begin() ; it != joystickComp->getInputs().end() ; ++it)
      for (auto it2 = it->second.begin() ; it2 != it->second.end() ; ++it2)
	actionstmp[it->first] |= this->_inputsJoystick[*it2];

  std::for_each(actionstmp.begin(), actionstmp.end(), [actionComp](const std::pair<std::string, bool> &pair)
		{
		  actionComp->setAction(pair.first, pair.second);
		});

}
