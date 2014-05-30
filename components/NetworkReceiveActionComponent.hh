#ifndef NETWORKRECEIVEACTIONCOMPONENT_H_
# define NETWORKRECEIVEACTIONCOMPONENT_H_

# include "ACopyableComponent.hpp"

class NetworkReceiveActionComponent : public ACopyableComponent<NetworkReceiveActionComponent>
{
public:
  NetworkReceiveActionComponent(unsigned int packet_num = 0);
  virtual	~NetworkReceiveActionComponent();
  virtual	void serialize(IBuffer &) const;
  virtual	void unserialize(IBuffer &);
  unsigned int	getPacketNum() const;
  void		setPacketNum(unsigned int);

  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;
protected:
  unsigned int	_packet_num;
};

#endif /* !NETWORKRECEIVEACTIONCOMPONENT_H_ */
