#ifndef COLLISIONPOINT_H_
# define COLLISIONPOINT_H_

# include "ACopyableComponent.hpp"
# include "Box2DComponent.hh"
# include "Pos2DComponent.hh"

class CollisionPoint : public ACopyableComponent<CollisionPoint>
{

protected:
  Pos2DComponent	*_pos;
  Box2DComponent	*_box;

public:
  CollisionPoint(float x = 0.f, float y = 0.f, float width = 0.f, float height = 0.f);
  virtual	~CollisionPoint();
  CollisionPoint(const CollisionPoint&);
  CollisionPoint	&operator=(const CollisionPoint&);
  virtual void		serialize(IBuffer &) const;
  virtual void		unserialize(IBuffer &);

  Box2DComponent	*getBox() const;
  Pos2DComponent	*getPos() const;

  virtual void		deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input);
  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

};

#endif /* !COLLISIONPOINT_H_ */
