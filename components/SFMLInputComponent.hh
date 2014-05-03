#ifndef		SFMLINPUTCOMPONENT_H_
# define	SFMLINPUTCOMPONENT_H_

#include <map>
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Event.hpp"
#include "AComponent.hh"

class		SFMLInputComponent : public AComponent
{
public:
  SFMLInputComponent();
  virtual ~SFMLInputComponent();
  const std::map<sf::Keyboard::Key, bool> getInputs() const;
  bool isActived(const sf::Keyboard::Key key) const;
  void setStatusKey(const sf::Keyboard::Key key, const bool status);

private:
  std::map<sf::Keyboard::Key, bool> _inputs;

};


#endif /* !SFMLINPUTCOMPONENT_H_ */
