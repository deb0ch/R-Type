#ifndef TAGCOMPONENT_H_
# define TAGCOMPONENT_H_

# include <vector>
# include "ACopyableComponent.hpp"

class TagComponent : public ACopyableComponent<TagComponent>
{
public:
  TagComponent();
  virtual	~TagComponent();

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  TagComponent*	addTag(const std::string& tag);
  bool		hasTag(const std::string& tag) const;
  void		removeTag(const std::string& tag);

  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  std::vector<std::string> _tags;
};

#endif /* !TAGCOMPONENT_H_ */
