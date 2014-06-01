#ifndef NETWORKSENDACTIONSYSTEM_H_
# define NETWORKSENDACTIONSYSTEM_H_

# include "ASystem.hh"
# include "INetworkRelay.hh"

class NetworkSendActionSystem : public ASystem
{
public:
  NetworkSendActionSystem(const std::vector<std::string> &serializable_action);
  virtual ~NetworkSendActionSystem();
  virtual bool canProcess(Entity *) const;
  virtual void beforeProcess(const float);
  virtual void processEntity(Entity *, const float);
protected:
  std::vector<std::string> _serializable_action;
  INetworkRelay *_network;
  std::string *_room_name;
};

#endif /* !NETWORKSENDACTIONSYSTEM_H_ */
