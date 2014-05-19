#ifndef NETWORKRECEIVEUPDATESYSTEM_H_
# define NETWORKRECEIVEUPDATESYSTEM_H_

# include "ASystem.hh"
# include "NetworkReceiveUpdateComponent.hh"

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
  void		unserializeComponent(Entity *, NetworkBuffer &buffer);
  void		updateEntity(Entity *, NetworkBuffer &buffer);
  void		getEntityInfos(NetworkBuffer &buffer,
			       unsigned int &id_entity, unsigned int &num_packet);
  bool		remoteEntityExists(unsigned int);

protected:
  std::vector<NetworkBuffer *> *_packets_to_apply;
};

#endif /* !NETWORKRECEIVEUPDATESYSTEM_H_ */
