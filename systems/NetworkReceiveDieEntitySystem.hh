#ifndef NETWORKRECEIVEDIEENTITYSYSTEM_H_
# define NETWORKRECEIVEDIEENTITYSYSTEM_H_

# include "ASystem.hh"
# include "INetworkRelay.hh"
# include "Room.hh"

class NetworkBuffer;

class NetworkReceiveDieEntitySystem : public ASystem
{
public:
  NetworkReceiveDieEntitySystem();
  virtual	~NetworkReceiveDieEntitySystem();

  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float);

  virtual void	beforeProcess(const float);
  virtual void	afterProcess(const float);

private:
  void		parsePacket(LockVector<IBuffer *> &vector, LockVector<IBuffer *>::iterator &it);

protected:
  INetworkRelay		*_network;
  std::string		*_room_name;
};

#endif /* !NETWORKRECEIVEDIEENTITYSYSTEM_H_ */
