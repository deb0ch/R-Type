#ifndef ASERIALIZABLECOMPONENT_H_
# define ASERIALIZABLECOMPONENT_H_

# include <string>
# include "AComponent.hh"
# include "IBuffer.hh"
# include "Remote.hh"

class ASerializableComponent : public AComponent
{
public:
  ASerializableComponent() = delete;
  ASerializableComponent(const std::string &type);
  virtual ~ASerializableComponent()
  {}

  ASerializableComponent *sendUpdate(bool);
  virtual void serialize(IBuffer &) const = 0;
  virtual void unserialize(IBuffer &) = 0;
  virtual void networkSerialize(Remote *remote, IBuffer &) const;
  virtual ASerializableComponent *clone() const = 0;
private:
  bool	_sendUpdate;
};

#endif /* !ASERIALIZABLECOMPONENT_H_ */
