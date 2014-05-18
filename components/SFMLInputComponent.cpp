#include	"SFMLInputComponent.hh"

SFMLInputComponent::SFMLInputComponent()
  : AComponent("SFMLInputComponent")
{
  this->_inputs["UP"]		= {sf::Keyboard::Key::Up, sf::Keyboard::Key::Z};
  this->_inputs["LEFT"]		= {sf::Keyboard::Key::Left, sf::Keyboard::Key::Q};
  this->_inputs["DOWN"]		= {sf::Keyboard::Key::Down, sf::Keyboard::Key::S};
  this->_inputs["RIGHT"]	= {sf::Keyboard::Key::Right, sf::Keyboard::Key::D};
  this->_inputs["FIRE"]		= {sf::Keyboard::Key::Space};
}

SFMLInputComponent::~SFMLInputComponent()
{}

const std::map<std::string, std::vector<sf::Keyboard::Key> >&	SFMLInputComponent::getInputs() const
{
  return (this->_inputs);
}

void	SFMLInputComponent::addInput(const std::string &action, const sf::Keyboard::Key &key)
{
  this->_inputs[action].push_back(key);
}

void SFMLInputComponent::serialize(IBuffer &) const
{}

void SFMLInputComponent::unserialize(IBuffer &)
{}
