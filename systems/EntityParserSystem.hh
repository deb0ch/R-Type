#ifndef ENTITY_PARSER_SYSTEM_H_
# define ENTITY_PARSER_SYSTEM_H_

# include <vector>
# include "ASystem.hh"

class EntityParserSystem : public ASystem
{
protected:
	virtual bool canProcess(Entity *);
	virtual void processEntity(Entity *, const float);

public:
	void addEntityToDelete(IEvent *entity);

public:
	EntityDeleterSystem();
	virtual ~EntityDeleterSystem();
	virtual void afterProcess();

private:
	std::vector<Entity *> _toDelete;

};

#endif /* !ENTITY_PARSER_SYSTEM_H_ */