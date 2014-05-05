#ifndef ENTITYDELETERSYSTEM_H_
# define ENTITYDELETERSYSTEM_H_

# include <vector>
# include "ASystem.hh"

class EntityDeleterSystem : public ASystem
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

#endif /* !ENTITYDELETERSYSTEM_H_ */
