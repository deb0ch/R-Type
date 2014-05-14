#ifndef ENTITYSPAWNERCOMPONENT_H_
# define ENTITYSPAWNERCOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		EntitySpawnerComponent : public AComponent<EntitySpawnerComponent>, public INetworkSerializableComponent
{
protected:
  float		_vX;
  float		_vY;

public:
		EntitySpawnerComponent(float x = 0.0f, float y = 0.0f);
		EntitySpawnerComponent(const EntitySpawnerComponent&);
  virtual	~EntitySpawnerComponent();
  EntitySpawnerComponent	&operator=(const EntitySpawnerComponent&);

  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);

  float		getVX() const;
  float		getVY() const;

  void		setVX(float x);
  void		setVY(float y);

  void		addVX(float x);
  void		addVY(float y);
};

#endif /* !ENTITYSPAWNERCOMPONENT_H_ */
