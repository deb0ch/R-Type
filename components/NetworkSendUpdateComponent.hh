#ifndef NETWORKUPDATECOMPONENT_H_
# define NETWORKUPDATECOMPONENT_H_

# include "AComponent.hpp"
# include "ISerializableComponent.hh"

class NetworkSendUpdateComponent : public AComponent<NetworkSendUpdateComponent>, public ISerializableComponent
{
public:
  NetworkSendUpdateComponent();
  virtual	~NetworkSendUpdateComponent();
  unsigned int	getPacketNumber() const;
  void		increasePacketNumber();
  virtual void serialize(IBuffer &) const;
  virtual void unserialize(IBuffer &);
protected:
  unsigned int	_packet_number;
};

#endif /* !NETWORKUPDATECOMPONENT_H_ */
