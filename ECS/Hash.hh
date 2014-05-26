#ifndef HASH_H_
# define HASH_H_

# include <string>
# include <cstdint>

typedef uint64_t hash_t;

class Hash
{
public:
  Hash();
  virtual ~Hash();
  hash_t operator()(const std::string &) const;
protected:

};

#endif /* !HASH_H_ */
