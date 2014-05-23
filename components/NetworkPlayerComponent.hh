#ifndef NETWORKPLAYERCOMPONENT_H_
# define NETWORKPLAYERCOMPONENT_H_

# include "ASerializableComponent.hh"
# include "ActionComponent.hh"

class NetworkPlayerComponent : public ASerializableComponent
{
public:
  NetworkPlayerComponent();
  NetworkPlayerComponent(const NetworkPlayerComponent &);
  virtual				~NetworkPlayerComponent();
  NetworkPlayerComponent		&operator=(const NetworkPlayerComponent &);

  virtual ASerializableComponent	*clone() const;
  virtual void				serialize(IBuffer &) const;
  virtual void				unserialize(IBuffer &);
  virtual void				networkSerialize(Remote *remote, IBuffer &) const;
protected:
  unsigned int				_remote_hash;
  std::vector<ASerializableComponent *>	_components;
  // May/Must segfault is a component is removed. Catch a remove component event to remove it from here?
};

#endif /* !NETWORKPLAYERCOMPONENT_H_ */
