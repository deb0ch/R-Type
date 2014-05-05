#ifndef SERIALIZER_H_
# define SERIALIZER_H_

# include <cstddef>
# include <iostream>
# include <algorithm>

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
  static int	serialize(char *str, unsigned int len, const T &elements)
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

  static int	unserialize(const char *str, unsigned int len, T &elements)
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

template <>
class Serializer<std::string>
{
public:
  static int		serialize(char *str, unsigned int lenght, const std::string &element)
  {
    unsigned int	lenght_written;

    lenght_written = 0;
    lenght_written += Serializer<unsigned int>::serialize(str + lenght_written,
							  lenght - lenght_written, element.length());
    std::cout << "STRING SIZE: " << element.length() << std::endl;
    for (auto it = element.begin(); it != element.end(); ++it)
      {
	if (lenght_written >= lenght)
	  {
	    std::cerr << "No more space" << std::endl;
	    throw 2;
	  }
	str[lenght_written] = *it;
	++lenght_written;
      }
    return (lenght_written);
  }

  static int		unserialize(const char *str, unsigned int lenght, std::string &element)
  {
    unsigned int	lenght_read;
    unsigned int	size;
    unsigned int	i;

    element = "";
    lenght_read = 0;
    lenght_read += Serializer<unsigned int>::unserialize(str + lenght_read,
							 lenght - lenght_read, size);
    std::cout << "GOT STRING SIZE: " << size << std::endl;
    for (i = 0; i < size; ++i)
      {
	if (lenght_read + i >= lenght)
	  {
	    std::cerr << "No more space" << std::endl;
	    throw 2;
	  }
	element += str[lenght_read + i];
      }
    return (lenght_read + i);
  }
};


#endif /* !SERIALIZER_H_ */
