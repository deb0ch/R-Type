#ifndef		SFMLINPUTCOMPONENT_H_
# define	SFMLINPUTCOMPONENT_H_

# include	<map>
# include	<string>

# include	"SFML/Window/Keyboard.hpp"

# include	"AComponent.hpp"

/**
 * @todo Repenser la gestion des inputs en faisant un autre component qui contient
 * les actions que peut faire l'entité. Elle contiendrait une map d'actions/boolean.
 * C'est cette map d'actions qui serait check par le(s) système(s) de contrôle (ActionSystem).
 * Ce composant serait aussi utilisé pour faire agir les monstre via les Systèmes de comportement (AIMoveAheadSystem, etc...).
 */
class		SFMLInputComponent : public AComponent<SFMLInputComponent>
{
private:
  std::map<sf::Keyboard::Key, std::string>	_inputs;

public:
  SFMLInputComponent();
  virtual ~SFMLInputComponent();

  const std::map<sf::Keyboard::Key, std::string>&	getInputs() const;
  const std::string&	getAction(const sf::Keyboard::Key key) const;
  void			setAction(const sf::Keyboard::Key key, const std::string &action);
};

#endif /* !SFMLINPUTCOMPONENT_H_ */
