#ifndef DISCONNECTPLAYERSYSTEM_H_
# define DISCONNECTPLAYERSYSTEM_H_

# include "ASystem.hh"

class DisconnectPlayerSystem : public ASystem
{
public:
  DisconnectPlayerSystem();
  virtual		~DisconnectPlayerSystem();
  virtual void		init();
  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float delta);
  void			disconnectPlayerHandler(IEvent *event);

};

#endif /* !DISCONNECTPLAYERSYSTEM_H_ */
