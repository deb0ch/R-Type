#ifndef OUTOFBOUNDSSYSTEM_H_
# define OUTOFBOUNDSSYSTEM_H_

# include "ASystem.hh"
# include "Window.hh"

class OutOfBoundsSystem : public ASystem
{

public:
  OutOfBoundsSystem();
  virtual ~OutOfBoundsSystem();

protected:
  virtual bool canProcess(Entity *) const;
  virtual void processEntity(Entity *, const float);

};

#endif /* !OUTOFBOUNDSSYSTEM_H_ */
