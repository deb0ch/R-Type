#ifndef NETWORKRECEIVEACTIONSYSTEM_H_
# define NETWORKRECEIVEACTIONSYSTEM_H_

# include "ASystem.hh"
# include "INetworkRelay.hh"
# include "LockVector.hpp"
# include "ActionComponent.hh"
# include "NetworkReceiveActionComponent.hh"

class NetworkReceiveActionSystem : public ASystem
{
public:
  NetworkReceiveActionSystem(const std::vector<std::string> &);
  virtual	~NetworkReceiveActionSystem();
  virtual	bool canProcess(Entity *) const;
  virtual	void beforeProcess(const float);
  virtual	void processEntity(Entity *, const float);
  void		parsePacket(Entity *, ActionComponent *action, NetworkReceiveActionComponent *network,
			    LockVector<IBuffer *> &vector, LockVector<IBuffer *>::iterator &it);
  void		parseActions(IBuffer &, ActionComponent *action);
protected:
  INetworkRelay			*_network;
  std::vector<std::string>	_serializable_action;
  std::string			*_room_name;
};

#endif /* !NETWORKRECEIVEACTIONSYSTEM_H_ */
