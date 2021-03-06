#ifndef NETWORKSENDUPDATESYSTEM_H_
# define NETWORKSENDUPDATESYSTEM_H_

# include "ASystem.hh"
# include "INetworkRelay.hh"
# include "Room.hh"
# include "LockVector.hpp"
# include "NetworkSendUpdateComponent.hh"

enum PacketType
  {
    ENTITY_UPDATE,
    ACTION_UPDATE,
    KILL_ENTITY
  };

class NetworkBuffer;

class NetworkSendUpdateSystem : public ASystem
{
public:
		NetworkSendUpdateSystem(const std::vector<std::string> &component_to_send);
  virtual	~NetworkSendUpdateSystem();

  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float delta);
  virtual void	beforeProcess(const float);
  virtual void	updateEntityToRemote(Remote *, const Entity *, NetworkSendUpdateComponent *);

private:
  void		serializeComponents(const Entity *, Remote *, IBuffer &buffer);
private:
  std::vector<std::string>		_component_to_send;
  INetworkRelay				*_network;
  std::string				*_room_name;
  static const int			_buffer_size = 512;
};

#endif /* !NETWORKSENDUPDATESYSTEM_H_ */
