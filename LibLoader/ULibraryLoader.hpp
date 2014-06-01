#ifndef _LIBRARYLOADER_H_
# define _LIBRARYLOADER_H_

#include <dlfcn.h>
#include <string>
#include <iostream>
#include <map>
#include "ILibraryLoader.hh"
#include "LibLoaderException.hh"

template <typename T>
class LibraryLoader : public ILibraryLoader<T>
{

public:
    typedef void * handle;

private:
  std::map<const std::string, handle> libs;

public:
  ~LibraryLoader();
  T *getInstance(const std::string &path, const std::string &entry);
  void clearLibraries();
  void clearLibrary(const std::string &path);

};

template <typename T>
LibraryLoader<T>::~LibraryLoader()
{
  this->clearLibraries();
}

template <typename T>
void		LibraryLoader<T>::clearLibraries()
{
  int		r;

  for (auto it = this->libs.begin(); it != this->libs.end(); ++it)
    if ((r = dlclose(it->second)))
      std::cerr << LibLoaderException(r).what() << std::endl;
  this->libs.clear();
}

template <typename T>
void		LibraryLoader<T>::clearLibrary(const std::string &path)
{
  auto it = this->libs.find(path);
  int		r;

  if (it == this->libs.end())
    return ;
  if ((r = dlclose(it->second)))
    std::cerr << LibLoaderException(r).what() << std::endl;
  this->libs.erase(it);
}

template <typename T>
T *LibraryLoader<T>::getInstance(const std::string &path, const std::string &entry)
{
  T		*(*instancier)();
  T		*res = NULL;
  handle	Handle = NULL;

  auto it = this->libs.find(path);
  std::cout << "PATH :" << path << std::endl;
  if (it == this->libs.end())
    {
      std::cout << "toto" << std::endl;
      Handle = dlopen(path.c_str(), RTLD_LAZY);
      this->libs[path] = Handle;
    }
  else
    Handle = it->second;
  if (Handle == NULL)
    throw LibLoaderException("Cant load " + entry);
  instancier = reinterpret_cast<T *(*)()>(dlsym(Handle, entry.c_str()));
  if (instancier)
    res = instancier();
  return (res);
}

#endif /* !_LIBRARYLOADER_H_ */
