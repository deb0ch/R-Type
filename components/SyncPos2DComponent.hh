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
  Pos2DComponent	&getSyncPos();
  float			getRatio() const;
  virtual void		serialize(IBuffer &) const;
  virtual void		unserialize(IBuffer &);
  virtual void		networkUnserializeCallback(IBuffer &, World *, Entity *);
protected:
  Pos2DComponent	_sync_pos;
  float			_ratio;
};

#endif /* !SYNCPOS2DCOMPONENT_H_ */
