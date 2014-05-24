#include "Hash.hh"

Hash::Hash()
{
}

Hash::~Hash()
{
}

unsigned long	Hash::operator()(const std::string &str) const
{
  unsigned long	result;

  result = 5381;
  for (auto it = str.begin(); it != str.end(); ++it)
    result = ((result << 5) + result) + *it;
  return (result);
}
