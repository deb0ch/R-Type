#ifndef NETWORKRECEIVEUPDATESYSTEM_H_
# define NETWORKRECEIVEUPDATESYSTEM_H_

# include "ASystem.hh"

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
  int		unserializeComponent(Entity *, const char *, int);
  void		updateEntity(Entity *, const char *, int);
  int		getEntityInfos(const char *buffer, int lenght,
			       unsigned int &id_entity, unsigned int &num_packet);

protected:
  std::vector< std::pair<const char *, int> > *_packets_to_apply;
};

#endif /* !NETWORKRECEIVEUPDATESYSTEM_H_ */
