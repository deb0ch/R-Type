#ifndef SERIALIZER_H_
# define SERIALIZER_H_

# include <cstddef>
# include <iostream>

const static short dummy_value = 0x00FF;
constexpr const static char *dummy_tab = reinterpret_cast<const char *>(&dummy_value);

constexpr static bool	isBigEndian()
{
  return (dummy_tab[0] == 0x00);
}

template <typename T>
class Serializer
{
private:

public:
  static void	serialize(std::string &str, const T &elements)
  {
    int		i;
    const char	*tab;

    tab = reinterpret_cast<const char *>(&elements);
    if (isBigEndian())
      i = 0;
    else
      i = sizeof(T);
    while ((isBigEndian() && i >= 0) || (!isBigEndian() && i < sizeof(T)))
      {
	str += tab[i];
	if (isBigEndian())
	  ++i;
	else
	  --i;
      }
  };

  static int	unserialize(std::string &str, T &elements)
  {
    int		i;
    char	*tab;
    auto	it = str.begin();

    tab = reinterpret_cast<char *>(&elements);
    if (isBigEndian())
      i = 0;
    else
      i = sizeof(T);
    while ((isBigEndian() && i >= 0) || (!isBigEndian() && i < sizeof(T)))
      {
	if (it == str.end())
	  {
	    std::cerr << "unserialize: Wrong size" << std::endl; // raise expression
	    return (-1);
	  }
	tab[i] = *it;
	if (isBigEndian())
	  ++i;
	else
	  --i;
	++it;
      }
    return (sizeof(T));
  }
};

#endif /* !SERIALIZER_H_ */
