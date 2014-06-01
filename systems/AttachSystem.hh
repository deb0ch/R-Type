#ifndef ATTACHSYSTEM_H_
# define ATTACHSYSTEM_H_

# include		"ASystem.hh"

class			AttachSystem : public ASystem
{
protected:
	virtual bool canProcess(Entity *);
	virtual void processEntity(Entity *, const float);

public:
	AttachSystem();
	virtual ~AttachSystem();
};

#endif /* !ATTACHSYSTEM_H_ */
