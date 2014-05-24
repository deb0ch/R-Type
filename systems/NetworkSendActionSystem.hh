#ifndef NETWORKSENDACTIONSYSTEM_H_
# define NETWORKSENDACTIONSYSTEM_H_

# include "ASystem.hh"
# include "INetworkRelay.hh"

class NetworkSendActionSystem : public ASystem
{
public:
  NetworkSendActionSystem(const std::vector<std::string> &serializable_action,
			  unsigned int spam_count = 10);
  virtual ~NetworkSendActionSystem();
  virtual bool canProcess(Entity *);
  virtual void beforeProcess();
  virtual void processEntity(Entity *, const float);
protected:
  std::vector<std::string> _serializable_action;
  const unsigned int _spam_count;
  INetworkRelay *_network;
  std::string *_room_name;
};

#endif /* !NETWORKSENDACTIONSYSTEM_H_ */
