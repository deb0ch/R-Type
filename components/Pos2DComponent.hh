#ifndef POS2DCOMPONENT_H_
# define POS2DCOMPONENT_H_

# include "ACopyableComponent.hpp"

class		Pos2DComponent : public ACopyableComponent<Pos2DComponent>
{
protected:
  float		_x;
  float		_y;

public:
		Pos2DComponent(float x = 0.0f, float y = 0.0f);
		Pos2DComponent(const Pos2DComponent&);
  virtual	~Pos2DComponent();
  Pos2DComponent	&operator=(const Pos2DComponent&);
  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  float		getX() const;
  float		getY() const;

  void		setX(float x);
  void		setY(float y);
};

#endif /* !POS2DCOMPONENT_H_ */
