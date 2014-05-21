#ifndef		SFMLINPUTCOMPONENT_H_
# define	SFMLINPUTCOMPONENT_H_

# include	<map>
# include	<string>
# include	<vector>

# include	"SFML/Window/Keyboard.hpp"
# include	"AComponent.hpp"
# include	"INetworkSerializableComponent.hh"

class		SFMLInputComponent : public AComponent<SFMLInputComponent>, public INetworkSerializableComponent
{
private:
  std::map<std::string, std::vector<sf::Keyboard::Key> >	_inputs;

public:
  SFMLInputComponent();
  virtual ~SFMLInputComponent();

  const std::map<std::string, std::vector<sf::Keyboard::Key> >&	getInputs() const;
  void			addInput(const std::string &action, const sf::Keyboard::Key &key);
  virtual void serialize(IBuffer &) const;
  virtual void unserialize(IBuffer &);
};

#endif /* !SFMLINPUTCOMPONENT_H_ */
