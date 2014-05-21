#ifndef FIREALWAYSCOMPONENT_H_
# define FIREALWAYSCOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		FireAlwaysComponent : public AComponent<FireAlwaysComponent>, public INetworkSerializableComponent
{
public:
		FireAlwaysComponent();
  virtual	~FireAlwaysComponent();

  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);
};

#endif /* !FIREALWAYSCOMPONENT_H_ */
