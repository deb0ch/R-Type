#ifndef SYNCPOS2DCOMPONENT_H_
# define SYNCPOS2DCOMPONENT_H_

# include "ACopyableComponent.hpp"
# include "Pos2DComponent.hh"

class SyncPos2DComponent : public ACopyableComponent<SyncPos2DComponent>
{
public:
  SyncPos2DComponent();
  virtual		~SyncPos2DComponent();
  const Pos2DComponent	&getSyncPos() const;
  virtual void		serialize(IBuffer &) const;
  virtual void		unserialize(IBuffer &);
protected:
  Pos2DComponent	_sync_pos;
};

#endif /* !SYNCPOS2DCOMPONENT_H_ */
