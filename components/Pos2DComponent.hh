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
  virtual	~Pos2DComponent();
  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);
  virtual void	additionalNetworkSerialize(IBuffer &) const;

  float		getX() const;
  float		getY() const;

  void		setX(float x);
  void		setY(float y);

  Pos2DComponent	operator+(const Pos2DComponent&);

  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !POS2DCOMPONENT_H_ */
