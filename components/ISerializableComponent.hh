#ifndef ISERIALIZABLECOMPONENT_H_
# define ISERIALIZABLECOMPONENT_H_

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

#endif /* !ISERIALIZABLECOMPONENT_H_ */
