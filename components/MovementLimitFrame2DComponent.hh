#ifndef MOVEMENTLIMITFRAME2DCOMPONENT_H_
# define MOVEMENTLIMITFRAME2DCOMPONENT_H_

# include "World.hh"
# include "Window.hh"
# include "ACopyableComponent.hpp"

class MovementLimitFrame2DComponent : public ACopyableComponent<MovementLimitFrame2DComponent>
{
public:
  MovementLimitFrame2DComponent(float posX = 0.f, float posY = 0.f,
				float width = WINDOW_WIDTH, float height = WINDOW_HEIGHT);
  virtual	~MovementLimitFrame2DComponent();
  		MovementLimitFrame2DComponent(const MovementLimitFrame2DComponent&);
  MovementLimitFrame2DComponent	&operator=(const MovementLimitFrame2DComponent&);

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  float		getPosX() const;
  float		getPosY() const;
  float		getWidth() const;
  float		getHeight() const;

  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  float		_posX;
  float		_posY;
  float		_width;
  float		_height;
};

#endif /* !MOVEMENTLIMITFRAME2DCOMPONENT_H_ */
