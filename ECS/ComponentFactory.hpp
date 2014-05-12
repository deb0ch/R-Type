#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include <map>
# include "Unistd.hh"
# include "Factory.hpp"
# include "IComponent.hh"
# include "Hash.hh"

#  ifdef _WIN32
#   include "WLibraryLoader.hpp"
#   include <sys/types.h>
#  elif __linux__
#   include "ULibraryLoader.hpp"
#   include <dirent.h>
#  endif

class ComponentFactory : public Factory<IComponent, unsigned long>
{
public:
  ComponentFactory(){
#  ifdef _WIN32
    this->_directory = "..\\plugin\\Debug\\";
#  elif __linux__
    this->_directory = "plugin/lib";
#  endif

    this->_loaderlib = LibraryLoader<IComponent>();
  }

  virtual ~ComponentFactory(){
  }

  virtual void init() {
    IComponent *input;
    DIR* rep = NULL;
    struct dirent* file = NULL;

    if ((rep = opendir(this->_directory.c_str())) == NULL)
      ; //TODO throw

    while ((file = readdir(rep)) != NULL)
      {
	input = NULL;
#  ifdef _WIN32
	if (auto it = std::string(file->d_name).find(".dll"))
	  input = _loaderlib.getInstance(this->_directory + file->d_name, "getInstance");
#  elif __linux__
	if (auto it = std::string(file->d_name).find(".so"))
	  {
	    std::cout << this->_directory + file->d_name << std::endl;
	    input = _loaderlib.getInstance(this->_directory + file->d_name, "getInstance");
	  }
#  endif
	if (input != NULL)
	  this->add(Hash()(input->getType()), input);
      }
    if (closedir(rep) == -1)
      ; //TODO throw
  }

private:
  LibraryLoader<IComponent> _loaderlib;
  std::string _directory;

};

#endif /* !COMPONENTFACTORY_H_ */
