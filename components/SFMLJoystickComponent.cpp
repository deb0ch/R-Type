#include	"SFMLJoystickComponent.hh"

SFMLJoystickComponent::SFMLJoystickComponent()
  : ACopyableComponent("SFMLJoystickComponent")
{
  this->_inputs["UP"]		= {SFMLJoystickEvent::JoystickButton::UP};
  this->_inputs["LEFT"]		= {SFMLJoystickEvent::JoystickButton::LEFT};
  this->_inputs["DOWN"]		= {SFMLJoystickEvent::JoystickButton::DOWN};
  this->_inputs["RIGHT"]	= {SFMLJoystickEvent::JoystickButton::RIGHT};
  this->_inputs["FIRE"]		= {SFMLJoystickEvent::JoystickButton::A, SFMLJoystickEvent::JoystickButton::X};
}

SFMLJoystickComponent::~SFMLJoystickComponent()
{}

const std::map<std::string, std::vector<SFMLJoystickEvent::JoystickButton> >&	SFMLJoystickComponent::getInputs() const
{
  return (this->_inputs);
}

void	SFMLJoystickComponent::addInput(const std::string &action, const SFMLJoystickEvent::JoystickButton &key)
{
  this->_inputs[action].push_back(key);
}

void SFMLJoystickComponent::serialize(IBuffer &) const
{}

void SFMLJoystickComponent::unserialize(IBuffer &)
{}

void	SFMLJoystickComponent::serializeFromFile(std::ofstream &, unsigned char) const
{}
