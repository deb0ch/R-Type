#ifndef ASERIALIZABLECOMPONENT_H_
# define ASERIALIZABLECOMPONENT_H_

# include <string>
# include "AComponent.hh"

class ASerializableComponent : public AComponent
{
public:
  ASerializableComponent(const std::string &);
  virtual ~ASerializableComponent();

  virtual std::string serialize() const;
protected:

};

#endif /* !ASERIALIZABLECOMPONENT_H_ */
