#ifndef NETWORKTIMEOUTENTITYSYSTEM_H_
# define NETWORKTIMEOUTENTITYSYSTEM_H_

# include "ASystem.hh"

class NetworkTimeOutEntitySystem : public ASystem
{
public:
  NetworkTimeOutEntitySystem();
  virtual		~NetworkTimeOutEntitySystem();

  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float delta);

};


#endif /* !NETWORKTIMEOUTENTITYSYSTEM_H_ */
