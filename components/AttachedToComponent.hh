#ifndef ATTACHEDTOCOMPONENT_H_
# define ATTACHEDTOCOMPONENT_H_

# include	"ACopyableComponent.hpp"

class		AttachedToComponent : public ACopyableComponent<AttachedToComponent>
{
public:
  AttachedToComponent(unsigned int id = 0, const std::pair<int, int> &offset = {0, 0});
  virtual	~AttachedToComponent();

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  unsigned int	getEntityIDAttachedTo() const;
  const std::pair<int, int> &getOffset() const;

  virtual void	networkUnserializeCallback(IBuffer &, World *world, Entity *);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  unsigned int		_entity_id;
  std::pair<int, int>	_offset;
};

#endif /* !ATTACHEDTOCOMPONENT_H_ */
