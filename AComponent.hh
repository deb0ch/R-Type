#ifndef ACOMPONENT_H_
# define ACOMPONENT_H_

# include <string>
# include "IComponent.hh"

class AComponent
{
public:
  AComponent() = delete;
  AComponent(const std::string &type);
  virtual ~AComponent();

  virtual const std::string &getType() const;
protected:
  std::string _type;
};

#endif /* !ACOMPONENT_H_ */
