#ifndef NETWORKUPDATECOMPONENT_H_
# define NETWORKUPDATECOMPONENT_H_

# include "ACopyableComponent.hpp"

class NetworkSendUpdateComponent : public ACopyableComponent<NetworkSendUpdateComponent>
{
public:
  NetworkSendUpdateComponent(const float update_rate = 1.f);
  virtual	~NetworkSendUpdateComponent();
  unsigned int	getPacketNumber() const;
  void		increasePacketNumber();
  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);
  float		getUpdateRate() const;
  NetworkSendUpdateComponent	*setUpdateRate(const float);
  void		addLastUpdateDelay(const float);
  bool		canSend();
  void		resetLastUpdateDelay();
  void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  unsigned int	_packet_number;
  float		_update_rate;
  float		_last_update_delay;
  bool		_first_update;
};

#endif /* !NETWORKUPDATECOMPONENT_H_ */
