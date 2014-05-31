#include	"SFMLJoystickEvent.hh"

SFMLJoystickEvent::SFMLJoystickEvent(const unsigned int key, const bool active)
  : AEvent("SFMLJoystickEvent"),
    _key(key), _active(active)
{}

SFMLJoystickEvent::~SFMLJoystickEvent()
{}
