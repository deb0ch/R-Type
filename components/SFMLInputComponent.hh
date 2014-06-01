#ifndef		SFMLINPUTCOMPONENT_H_
# define	SFMLINPUTCOMPONENT_H_

# include	<string>

# include	"ACopyableComponent.hpp"

class		SFMLInputComponent : public ACopyableComponent<SFMLInputComponent>
{
public:
  SFMLInputComponent();
  virtual ~SFMLInputComponent();

  virtual void serialize(IBuffer &) const;
  virtual void unserialize(IBuffer &);

  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !SFMLINPUTCOMPONENT_H_ */
