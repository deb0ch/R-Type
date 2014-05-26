#ifndef ACOPYABLECOMPONENT_H_
# define ACOPYABLECOMPONENT_H_

# include "ASerializableComponent.hh"

template <typename T>
class ACopyableComponent : public ASerializableComponent
{
public:
  ACopyableComponent() = delete;
  ACopyableComponent(const std::string &type) : ASerializableComponent(type)
  {}
  virtual ~ACopyableComponent()
  {}

  virtual ASerializableComponent *cloneSerializable() const
  {
    return (new T(*dynamic_cast<const T *>(this)));
  }
protected:

};

#endif /* !ACOPYABLECOMPONENT_H_ */
