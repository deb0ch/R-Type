#ifndef SPEED2DCOMPONENT_H_
# define SPEED2DCOMPONENT_H_

# include "ACopyableComponent.hpp"

class		Speed2DComponent : public ACopyableComponent<Speed2DComponent>
{
protected:
  float		_vX;
  float		_vY;

public:
		Speed2DComponent(float x = 0.0f, float y = 0.0f);
  virtual	~Speed2DComponent();

  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);

  float		getVX() const;
  float		getVY() const;

  void		setVX(float x);
  void		setVY(float y);

  void		addVX(float x);
  void		addVY(float y);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !SPEED2DCOMPONENT_H_ */
