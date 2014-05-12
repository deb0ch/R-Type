#ifndef ISERIALIZABLECOMPONENT_H_
# define ISERIALIZABLECOMPONENT_H_

# include <string>
# include "IComponent.hh"
# include "IBuffer.hh"

class ISerializableComponent
{
public:
  virtual ~ISerializableComponent()
  {}

  virtual void serialize(IBuffer &) const = 0;
  virtual void unserialize(IBuffer &) = 0;
protected:

};

#endif /* !ISERIALIZABLECOMPONENT_H_ */
