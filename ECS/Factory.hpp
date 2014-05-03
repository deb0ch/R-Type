#ifndef FACTORY_H_
# define FACTORY_H_

# include <map>

template <typename U, typename Key = std::string>
class Factory
{
public:
  Factory()
  {}
  virtual ~Factory()
  {}

  template <typename T>
  void	add(const std::string &type)
  {
    this->_types.insert(std::make_pair(type, &Factory::makeInstance<T>));
  }

  U	*create(const std::string &type) const
  {
    auto it = this->_types.find(type);

    if (it == this->_types.end())
      return (NULL);
    return ((this->*(it->second))());
  }

private:
  template <typename X>
  U	*makeInstance() const
  {
    return (static_cast<U *>(new X()));
  }
protected:
  std::map<Key, U * (Factory::*)() const> _types;
};

#endif /* !FACTORY_H_ */
