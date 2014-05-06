#include	"SFMLKeyEvent.hh"

SFMLKeyEvent::SFMLKeyEvent(const sf::Keyboard::Key key, const bool active)
  : AEvent("SFMLKeyEvent"),
    _key(key), _active(active)
{}

SFMLKeyEvent::~SFMLKeyEvent()
{}
