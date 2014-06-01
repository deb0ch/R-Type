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

bool	SFMLInputSystem::canProcess(Entity *e) const {
  if (e->hasComponent("ActionComponent"))
    return (true);
  return (false);
}

const std::map<std::string, std::vector<sf::Keyboard::Key> >	&SFMLInputSystem::getKeyboardInputs() const
{
  static std::map<std::string, std::vector<sf::Keyboard::Key> >	res;

  if (res.size() == 0)
    {
      res["UP"]		= {sf::Keyboard::Key::Up, sf::Keyboard::Key::Z};
      res["LEFT"]	= {sf::Keyboard::Key::Left, sf::Keyboard::Key::Q};
      res["DOWN"]	= {sf::Keyboard::Key::Down, sf::Keyboard::Key::S};
      res["RIGHT"]	= {sf::Keyboard::Key::Right, sf::Keyboard::Key::D};
      res["FIRE"]	= {sf::Keyboard::Key::Space};
    }

  return (res);
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
    for (auto it = this->getKeyboardInputs().begin() ; it != this->getKeyboardInputs().end() ; ++it)
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
