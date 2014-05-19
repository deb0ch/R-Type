#ifndef NETWORKRECEIVEUPDATESYSTEM_H_
# define NETWORKRECEIVEUPDATESYSTEM_H_

# include "ASystem.hh"
# include "NetworkReceiveUpdateComponent.hh"
# include "LockVector.hpp"
# include "INetworkRelay.hh"
# include "Room.hh"

class NetworkBuffer;

class NetworkReceiveUpdateSystem : public ASystem
{
public:
		NetworkReceiveUpdateSystem();
  virtual	~NetworkReceiveUpdateSystem();
  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);

  virtual void	beforeProcess();
  virtual void	afterProcess();

private:
  void		unserializeComponent(Entity *, IBuffer &buffer);
  void		updateEntity(Entity *, IBuffer &buffer);
  void		getEntityInfos(IBuffer &buffer,
			       unsigned int &id_entity, unsigned int &num_packet);
  bool		remoteEntityExists(unsigned int);
  void		parsePacketOnEntity(Entity *entity, NetworkReceiveUpdateComponent *receive_component,
				    LockVector<IBuffer *> &vector, LockVector<IBuffer *>::iterator &it);
  void		parsePacket(LockVector<IBuffer *> &vector, LockVector<IBuffer *>::iterator &it);


protected:
  INetworkRelay	*_network;
  std::string	*_room_name;
};

#endif /* !NETWORKRECEIVEUPDATESYSTEM_H_ */
