#ifndef SYNCPOS2DSYSTEM_H_
# define SYNCPOS2DSYSTEM_H_

# include "ASystem.hh"

class SyncPos2DSystem : public ASystem
{
public:
  SyncPos2DSystem();
  virtual ~SyncPos2DSystem();

  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

};

#endif /* !SYNCPOS2DSYSTEM_H_ */
