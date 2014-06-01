#ifndef RESETACTIONSYSTEM_H_
# define RESETACTIONSYSTEM_H_

# include "ASystem.hh"

class ResetActionSystem : public ASystem
{
public:
	ResetActionSystem();
	virtual ~ResetActionSystem();
	virtual bool canProcess(Entity *) const;
	virtual void processEntity(Entity *, const float);
};

#endif /* !RESETACTIONSYSTEM_H_ */