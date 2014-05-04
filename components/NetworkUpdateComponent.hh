#ifndef NETWORKUPDATECOMPONENT_H_
# define NETWORKUPDATECOMPONENT_H_

# include "AComponent.hpp"

class NetworkUpdateComponent : public AComponent<NetworkUpdateComponent>
{
public:
  NetworkUpdateComponent();
  virtual ~NetworkUpdateComponent();
  int	getPacketNumber() const;
  void	increasePacketNumber();
protected:
  int	_packet_number;
};

#endif /* !NETWORKUPDATECOMPONENT_H_ */
