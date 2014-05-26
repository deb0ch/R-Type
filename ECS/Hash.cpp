#include "Hash.hh"

Hash::Hash()
{}

Hash::~Hash()
{}

hash_t	Hash::operator()(const std::string &str) const
{
  hash_t	result;

  result = 5381;
  for (auto it = str.begin(); it != str.end(); ++it)
    result = ((result << 5) + result) + *it;
  return (result);
}
