#ifndef ENTITYDELETERSYSTEM_H_
# define ENTITYDELETERSYSTEM_H_

# include <vector>
# include "ASystem.hh"

class EntityDeleterSystem : public ASystem
{
protected:
  virtual bool canProcess(Entity *) const;
  virtual void processEntity(Entity *, const float);

public:

  void addEntityToDelete(IEvent *entity);

  EntityDeleterSystem();
  virtual ~EntityDeleterSystem();
  virtual void afterProcess(const float);

private:
  std::vector<Entity *> _toDelete;

};

#endif /* !ENTITYDELETERSYSTEM_H_ */
