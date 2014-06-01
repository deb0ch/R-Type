#ifndef ATTACHEDTOSYSTEM_H_
# define ATTACHEDTOSYSTEM_H_

# include		"ASystem.hh"

class			AttachedToSystem : public ASystem
{
protected:
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *, const float);

public:
  AttachedToSystem();
  virtual ~AttachedToSystem();
};


#endif /* !ATTACHEDTOSYSTEM_H_ */
