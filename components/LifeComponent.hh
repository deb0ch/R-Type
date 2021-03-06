#ifndef LIFECOMPONENT_H_
# define LIFECOMPONENT_H_

# include	"ACopyableComponent.hpp"

class		LifeComponent : public ACopyableComponent<LifeComponent>
{
public:
	LifeComponent(unsigned int life = 100, float invulnerability = 0);
	virtual	~LifeComponent();
	virtual void	serialize(IBuffer &) const;
	virtual void	unserialize(IBuffer &);

	unsigned int	getLife() const;
	void decreaseLife(const unsigned int);
	void gainLife(const unsigned int);

	bool isInvulnerable() const;
	void decreaseInvulnerability(float delta);
	void setInvulnerabilityTime(float time);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
	unsigned int _life;
	float _invulnerabilityMaxTime;
	float _invulnerability;
};

#endif /* !LIFECOMPONENT_H_ */
