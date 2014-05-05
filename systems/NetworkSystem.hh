#ifndef NETWORKSYSTEM_H_
# define NETWORKSYSTEM_H_

# include "ASystem.hh"

enum PacketType
  {
    ENTITY_UPDATE
  };

class NetworkSystem : public ASystem
{
public:
		NetworkSystem(const std::vector<std::string> &component_to_send);
  virtual	~NetworkSystem();

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float delta);
private:
  int		serializeComponents(Entity *, char *buffer, int buffer_size);
private:
  std::vector<std::string> _component_to_send;
  static const int _buffer_size = 512;
};

#endif /* !NETWORKSYSTEM_H_ */
