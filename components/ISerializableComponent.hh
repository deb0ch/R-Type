#ifndef ASERIALIZABLECOMPONENT_H_
# define ASERIALIZABLECOMPONENT_H_

# include <string>
# include "IComponent.hh"

class ISerializableComponent
{
public:
  virtual ~ISerializableComponent()
  {}

  virtual int serialize(char *buffer, int lenght) const = 0;
  virtual int unserialize(const char *buffer, int lenght) = 0;
protected:

};

#endif /* !ASERIALIZABLECOMPONENT_H_ */
