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

  void	add(const Key &key, const U *obj)
  {
    auto it = this->_types.find(key);

    if (it == this->_types.end())
      this->_types.insert(std::make_pair(key, obj));
  }

  U	*create(const Key &key) const
  {
    auto it = this->_types.find(key);

    if (it == this->_types.end())
      return (NULL);
    return it->second->clone();
  }

protected:
  std::map<Key, const U *> _types;
};

#endif /* !FACTORY_H_ */
