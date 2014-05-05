#ifndef NETWORKSENDUPDATESYSTEM_H_
# define NETWORKSENDUPDATESYSTEM_H_

# include "ASystem.hh"

enum PacketType
  {
    ENTITY_UPDATE
  };

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
  int		serializeComponents(Entity *, char *buffer, int buffer_size);
private:
  std::vector<std::string> _component_to_send;
  std::vector< std::pair<const char *, int> > *_packets_sended;
  static const int _buffer_size = 512;
};

#endif /* !NETWORKSENDUPDATESYSTEM_H_ */
