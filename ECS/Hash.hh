#ifndef HASH_H_
# define HASH_H_

# include <string>

class Hash
{
public:
  Hash();
  virtual ~Hash();
  unsigned long operator()(const std::string &) const;
protected:

};

#endif /* !HASH_H_ */
