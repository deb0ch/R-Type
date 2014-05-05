#ifndef		SFMLINPUTCOMPONENT_H_
# define	SFMLINPUTCOMPONENT_H_

#include	<map>

#include	"SFML/Window/Keyboard.hpp"
#include	"SFML/Window/Event.hpp"

#include	"AComponent.hpp"

/**
 * @todo Repenser la gestion des inputs en faisant un autre component qui contient
 * les actions que peut faire l'entité. Elle contiendrait une map d'actions/boolean.
 * C'est cette map d'actions qui serait check par le(s) système(s) de contrôle (ActionSystem).
 * Ce composant serait aussi utilisé pour faire agir les monstre via les Systèmes de comportement (AIMoveAheadSystem, etc...).
 */
class		SFMLInputComponent : public AComponent<SFMLInputComponent>
{
private:
  std::map<sf::Keyboard::Key, bool>	_inputs;

public:
  SFMLInputComponent();
  virtual ~SFMLInputComponent();
  const std::map<sf::Keyboard::Key, bool>	getInputs() const;
  bool						isActived(const sf::Keyboard::Key key) const;
  void						setStatusKey(const sf::Keyboard::Key key, const bool status);
};

#endif /* !SFMLINPUTCOMPONENT_H_ */
