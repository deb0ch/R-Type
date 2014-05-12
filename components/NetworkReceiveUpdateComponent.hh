#ifndef NETWORKRECEIVEUPDATECOMPONENT_H_
# define NETWORKRECEIVEUPDATECOMPONENT_H_

# include "AComponent.hpp"
# include "ISerializableComponent.hh"

class NetworkReceiveUpdateComponent : public AComponent<NetworkReceiveUpdateComponent>
{
public:
		NetworkReceiveUpdateComponent(unsigned int remote_id = 0,
					      unsigned int packet_num = 0);
  virtual	~NetworkReceiveUpdateComponent();
  unsigned int	getRemoteID() const;
  void		setRemoteID(unsigned int);
  unsigned int	getPacketNum() const;
  void		setPacketNum(unsigned int);
protected:
  unsigned int	_remote_id;
  unsigned int	_packet_num;
};

#endif /* !NETWORKRECEIVEUPDATECOMPONENT_H_ */
