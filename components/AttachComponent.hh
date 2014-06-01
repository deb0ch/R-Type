#ifndef ATTACHCOMPONENT_H_
# define ATTACHCOMPONENT_H_

# include	"ACopyableComponent.hpp"

class		AttachComponent : public ACopyableComponent<AttachComponent>
{
public:
  AttachComponent(const std::string &entity_name = "");
  virtual	~AttachComponent();
  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  bool		isInitiliazed() const;
  void		setInitiliazed();
  const std::string &getEntityName() const;

  virtual void	deserializeFromFileSpecial(const std::string &lastline,
					   std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  std::string		_entity_name;
  bool			_initialized;
};

#endif /* !ATTACHCOMPONENT_H_ */
