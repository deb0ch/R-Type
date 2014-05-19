#ifndef RECEIVEUDPSYSTEM_H_
# define RECEIVEUDPSYSTEM_H_

# include "ASystem.hh"

class ReceiveUDPSystem : public ASystem
{
public:
  ReceiveUDPSystem();
  virtual ~ReceiveUDPSystem();
  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);
  virtual void	beforeProcess();
protected:

};

#endif /* !RECEIVEUDPSYSTEM_H_ */
