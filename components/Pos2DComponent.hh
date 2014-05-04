#ifndef POS2DCOMPONENT_H_
# define POS2DCOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"

class		Pos2DComponent : public AComponent<Pos2DComponent>, public ISerializableComponent
{
protected:
  float		_x;
  float		_y;

public:
		Pos2DComponent(float x = 0.0f, float y = 0.0f);
		Pos2DComponent(const Pos2DComponent&);
  virtual	~Pos2DComponent();
  Pos2DComponent	&operator=(const Pos2DComponent&);
  virtual std::string serialize() const;

  float		getX() const;
  float		getY() const;

  void		setX(float x);
  void		setY(float y);
};

#endif /* !POS2DCOMPONENT_H_ */
