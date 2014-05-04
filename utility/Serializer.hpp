#ifndef SERIALIZER_H_
# define SERIALIZER_H_

# include <cstddef>
# include <iostream>

const static short dummy_value = 0x00FF;

# ifdef __linux__
constexpr 
# endif
const static char *dummy_tab = reinterpret_cast<const char *>(&dummy_value);

# ifdef __linux__
constexpr 
# endif
static bool	isBigEndian()
{
  return (dummy_tab[0] == 0x00);
}

template <typename T>
class Serializer
{
private:

public:
  static int	serialize(char *str, int len, const T &elements)
  {
    int		i;
    int		j;
    const char	*tab;

    tab = reinterpret_cast<const char *>(&elements);
    if (len < sizeof(T))
      {
	std::cout << "Not enough space" << std::endl; // raise exception
	return (0);
      }
    if (isBigEndian())
      i = 0;
    else
      i = sizeof(T) - 1;
    j = 0;
    while ((isBigEndian() && i < sizeof(T)) || (!isBigEndian() && i >= 0))
      {
	if (j >= len)
	  {
	    std::cerr << "serialize: Wrong size" << std::endl; // raise expression
	    return (0);
	  }
	str[j] = tab[i];
	if (isBigEndian())
	  ++i;
	else
	  --i;
	++j;
      }
    return (sizeof(T));
  };

  static int	unserialize(const char *str, int len, T &elements)
  {
    int		i;
    int		j;
    char	*tab;

    tab = reinterpret_cast<char *>(&elements);
    if (len < sizeof(T))
      {
	std::cout << "Not enough space" << std::endl; // raise exception
	return (0);
      }
    if (isBigEndian())
      i = 0;
    else
      i = sizeof(T) - 1;
    j = 0;
    while ((isBigEndian() && i < sizeof(T)) || (!isBigEndian() && i >= 0))
      {
	if (j >= len)
	  {
	    std::cerr << "unserialize: Wrong size" << std::endl; // raise exception
	    return (0);
	  }
	tab[j] = str[i];
	if (isBigEndian())
	  ++i;
	else
	  --i;
	++j;
      }
    return (sizeof(T));
  }
};

#endif /* !SERIALIZER_H_ */
