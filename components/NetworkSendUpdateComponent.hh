#ifndef NETWORKUPDATECOMPONENT_H_
# define NETWORKUPDATECOMPONENT_H_

# include "AComponent.hpp"

class NetworkSendUpdateComponent : public AComponent<NetworkSendUpdateComponent>
{
public:
		NetworkSendUpdateComponent();
  virtual	~NetworkSendUpdateComponent();
  unsigned int	getPacketNumber() const;
  void		increasePacketNumber();
protected:
  unsigned int	_packet_number;
};

#endif /* !NETWORKUPDATECOMPONENT_H_ */
