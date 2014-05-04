#ifndef ASERIALIZABLECOMPONENT_H_
# define ASERIALIZABLECOMPONENT_H_

# include <string>
# include "IComponent.hh"

class ISerializableComponent
{
public:
  virtual ~ISerializableComponent()
  {}

  virtual std::string serialize() const = 0;
protected:

};

#endif /* !ASERIALIZABLECOMPONENT_H_ */
