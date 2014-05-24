#ifndef ASERIALIZABLECOMPONENT_H_
# define ASERIALIZABLECOMPONENT_H_

# include <string>
# include "AComponent.hh"
# include "IBuffer.hh"
# include "Remote.hh"

class ASerializableComponent : public AComponent
{
public:
  ASerializableComponent() = delete;
  ASerializableComponent(const std::string &type);
  virtual ~ASerializableComponent()
  {}

  ASerializableComponent *setNetworkSendUpdate(bool);
  ASerializableComponent *setNetworkSend(bool);
  virtual void serialize(IBuffer &) const = 0;
  virtual void unserialize(IBuffer &) = 0;
  virtual void networkSerialize(Remote *remote, IBuffer &, bool force_send = false) const;
  virtual ASerializableComponent *cloneSerializable() const = 0;
  virtual IComponent *clone() const;
protected:
  bool	_sendUpdate;
  bool	_send;
};

#endif /* !ASERIALIZABLECOMPONENT_H_ */
