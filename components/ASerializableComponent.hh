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

  ASerializableComponent	*setNetworkSendUpdateException(unsigned int);
  ASerializableComponent	*setNetworkCanSendUpdate(bool);
  ASerializableComponent	*setNetworkCanSend(bool);
  ASerializableComponent	*setNetworkSendException(unsigned int);
  bool				canSend(unsigned int) const;
  bool				canSendUpdate(unsigned int) const;
  virtual void serialize(IBuffer &) const = 0;
  virtual void unserialize(IBuffer &) = 0;
  virtual void networkSerialize(Remote *remote, IBuffer &, bool force_send = false) const;
  virtual void additionalNetworkSerialize(IBuffer &) const;
  virtual ASerializableComponent *cloneSerializable() const = 0;
  virtual IComponent *clone() const;
protected:
  std::vector<unsigned int>	_exception_send_update;
  std::vector<unsigned int>	_exception_send;
  bool				_can_send_update;
  bool				_can_send;
};

#endif /* !ASERIALIZABLECOMPONENT_H_ */
