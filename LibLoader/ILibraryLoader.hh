#ifndef __ILIBRARYLOADER_H_
# define __ILIBRARYLOADER_H_

# include <string>

template <typename T>
class ILibraryLoader
{
public:
  virtual T *getInstance(const std::string &path, const std::string &entry = "getInstance") = 0;
  virtual void clearLibraries() = 0;
  virtual void clearLibrary(const std::string &path) = 0;

  virtual ~ILibraryLoader() {}
};

/*
class ILibraryLoader
{
public:
	virtual IAnimal *getInstance(const std::string &path, const std::string &entry = "getInstance") = 0;
};
*/
#endif /* !__ILIBRARYLOADER_H_ */
