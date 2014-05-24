#ifndef NETWORKSENDACTIONCOMPONENT_H_
# define NETWORKSENDACTIONCOMPONENT_H_

# include "ACopyableComponent.hpp"

class NetworkSendActionComponent : public ACopyableComponent<NetworkSendActionComponent>
{
public:
  NetworkSendActionComponent(unsigned int id = 0);
  virtual	~NetworkSendActionComponent();
  unsigned int	getPacketNumber() const;
  void		increasePacketNumber();
  unsigned int	getRemoteId() const;
  void		setRemoteId(unsigned int);
  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);
protected:
  unsigned int	_packet_number;
  unsigned int	_remote_id;
};

#endif /* !NETWORKSENDACTIONCOMPONENT_H_ */
