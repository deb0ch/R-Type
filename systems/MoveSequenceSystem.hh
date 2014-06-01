#ifndef MOVESEQUENCESYSTEM_H_
# define MOVESEQUENCESYSTEM_H_

# include "ASystem.hh"

class MoveSequenceSystem : public ASystem
{
public:
	MoveSequenceSystem();
	virtual ~MoveSequenceSystem();
	virtual bool canProcess(Entity *) const;
	virtual void processEntity(Entity *, const float);
};

#endif /* !MOVESEQUENCESYSTEM_H_ */
