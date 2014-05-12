#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include <map>
# include "Factory.hpp"
# include "IComponent.hh"
# include ""

#  ifdef _WIN32
#   include "WLibraryLoader.hpp"
#   define PATH "Ressources\\Images\\"
#   define PATHLIB "..\\plugin\\Debug\\"
#   define EXTENSION ".dll"
#  elif __linux__
#   include <unistd.h>
#   include "ULibraryLoader.hpp"
#   define PATH "Ressources/Images/"
#   define PATHLIB "plugin/lib"
#   define EXTENSION ".so"
#  endif


class ComponentFactory : public Factory<IComponent, unsigned long>
{
public:
  ComponentFactory(){
    this->_loaderlib = LibraryLoader<IComponent>();
  }
  virtual ~ComponentFactory(){
  }

  virtual void init() {
    IComponent *input = NULL;
    input = this->_loaderlib.getInstance(PATHLIB + std::string("NameFile") + EXTENSION, "getInstance");
    this->add()
  }
private:
  LibraryLoader<IComponent> _loaderlib;

};

#endif /* !COMPONENTFACTORY_H_ */
