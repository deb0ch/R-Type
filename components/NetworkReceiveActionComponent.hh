#ifndef NETWORKRECEIVEACTIONCOMPONENT_H_
# define NETWORKRECEIVEACTIONCOMPONENT_H_

# include "AComponent.hpp"
# include "ISerializableComponent.hh"

class NetworkReceiveActionComponent : public AComponent<NetworkReceiveActionComponent>
{
public:
  NetworkReceiveActionComponent(unsigned int packet_num = 0);
  virtual	~NetworkReceiveActionComponent();
  unsigned int	getPacketNum() const;
  void		setPacketNum(unsigned int);
protected:
  unsigned int	_packet_num;
};

#endif /* !NETWORKRECEIVEACTIONCOMPONENT_H_ */
