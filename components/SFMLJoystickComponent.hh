#ifndef		SFMLJOYSTICKCOMPONENT_H_
# define	SFMLJOYSTICKCOMPONENT_H_

# include	<map>
# include	<string>
# include	<vector>

# include	"ACopyableComponent.hpp"
# include	"SFMLJoystickEvent.hh"

class		SFMLJoystickComponent : public ACopyableComponent<SFMLJoystickComponent>
{
private:
  std::map<std::string, std::vector<SFMLJoystickEvent::JoystickButton> >	_inputs;

public:
  SFMLJoystickComponent();
  virtual ~SFMLJoystickComponent();

  const std::map<std::string, std::vector<SFMLJoystickEvent::JoystickButton> >&	getInputs() const;
  void	addInput(const std::string &action, const SFMLJoystickEvent::JoystickButton &key);
  virtual void serialize(IBuffer &) const;
  virtual void unserialize(IBuffer &);

  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !SFMLJOYSTICKCOMPONENT_H_ */
