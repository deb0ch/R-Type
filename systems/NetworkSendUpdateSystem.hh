#ifndef NETWORKSENDUPDATESYSTEM_H_
# define NETWORKSENDUPDATESYSTEM_H_

# include "ASystem.hh"

enum PacketType
  {
    ENTITY_UPDATE
  };

class NetworkBuffer;

class NetworkSendUpdateSystem : public ASystem
{
public:
		NetworkSendUpdateSystem(const std::vector<std::string> &component_to_send);
  virtual	~NetworkSendUpdateSystem();

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float delta);
  virtual void	beforeProcess();
  virtual void	start();

private:
  void		serializeComponents(Entity *, NetworkBuffer &buffer);
private:
  std::vector<std::string>		_component_to_send;
  std::vector< NetworkBuffer * >	*_packets_sended;
  static const int			_buffer_size = 512;
};

#endif /* !NETWORKSENDUPDATESYSTEM_H_ */
