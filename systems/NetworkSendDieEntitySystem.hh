#ifndef NETWORKSENDDIEENTITY_H_
# define NETWORKSENDDIEENTITY_H_

# include "INetworkRelay.hh"
# include "Room.hh"
# include "ASystem.hh"

class NetworkSendDieEntitySystem : public ASystem
{
protected:
  virtual bool canProcess(Entity *) const;
  virtual void processEntity(Entity *, const float);
  virtual void beforeProcess(const float);

public:
  void addEntityToDelete(IEvent *entity);

public:
  NetworkSendDieEntitySystem();
  virtual ~NetworkSendDieEntitySystem();
  virtual void afterProcess(const float);

private:
  std::vector<Entity *> _toDelete;
  INetworkRelay *_network;
  std::string *_room_name;

};

#endif /* !NETWORKSENDDIEENTITY_H_ */
