#ifndef FIREALWAYSCOMPONENT_H_
# define FIREALWAYSCOMPONENT_H_

# include	"ACopyableComponent.hpp"

class		FireAlwaysComponent : public ACopyableComponent<FireAlwaysComponent>
{
public:
		FireAlwaysComponent();
  virtual	~FireAlwaysComponent();

  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);
};

#endif /* !FIREALWAYSCOMPONENT_H_ */
