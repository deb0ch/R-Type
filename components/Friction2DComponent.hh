#ifndef FRICTION2DCOMPONENT_H_
# define FRICTION2DCOMPONENT_H_

# include "ACopyableComponent.hpp"

class		Friction2DComponent : public ACopyableComponent<Friction2DComponent>
{
public:
  float		getFrictionCoef() const;
  void		setFrictionCoef(float coef);

public:
		Friction2DComponent(float coef = 0.1);
  virtual	~Friction2DComponent();

  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  float		_frictionCoef;
};

#endif /* !FRICTION2DCOMPONENT_H_ */
