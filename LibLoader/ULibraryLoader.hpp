#ifndef _LIBRARYLOADER_H_
# define _LIBRARYLOADER_H_

#include <dlfcn.h>
#include <string>
#include <iostream>
#include <map>
#include "ILibraryLoader.hh"

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
  auto it = this->libs.begin();

  for (it = this->libs.begin(); it != this->libs.end(); ++it)
    if (dlclose(it->second))
      throw(1);
  this->libs.clear();
}

template <typename T>
void		LibraryLoader<T>::clearLibrary(const std::string &path)
{
  auto it = this->libs.find(path);

  if (it == this->libs.end())
    return ;
  if (dlclose(it->second))
    throw(1);
  this->libs.erase(it);
}

template <typename T>
T *LibraryLoader<T>::getInstance(const std::string &path, const std::string &entry)
{
  T		*(*instancier)();
  T		*res = NULL;
  handle	Handle = NULL;

  auto it = this->libs.find(path);
  if (it == this->libs.end())
    {
      std::cout << "toto" << std::endl;
      Handle = dlopen(path.c_str(), RTLD_LAZY);
      this->libs[path] = Handle;
    }
  else
    Handle = it->second;
  if (Handle == NULL)
    throw (1);
  instancier = reinterpret_cast<T *(*)()>(dlsym(Handle, entry.c_str()));
  if (instancier)
    res = instancier();
  return (res);
}

#endif /* !_LIBRARYLOADER_H_ */
