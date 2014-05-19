#ifndef TAGCOMPONENT_H_
# define TAGCOMPONENT_H_

# include <vector>

# include "AComponent.hpp"
# include "INetworkSerializableComponent.hh"

class TagComponent : public AComponent<TagComponent>, public INetworkSerializableComponent
{
public:
  TagComponent();
  virtual	~TagComponent();

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  void addTag(const std::string& tag);
  bool hasTag(const std::string& tag) const;
  void removeTag(const std::string& tag);

protected:
  std::vector<std::string > _tags;

};

#endif /* !TAGCOMPONENT_H_ */
