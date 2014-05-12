#ifndef ICOMPONENT_H_
# define ICOMPONENT_H_

# include <string>

#if _WIN32
	#define DECLSPEC __declspec(dllexport)
#elif __linux__
	#define DECLSPEC
#endif

class		IComponent
{
public:
		IComponent() {};
  virtual	~IComponent() {};

  virtual const std::string	&getType() const = 0;
  virtual IComponent *clone() const = 0;
};

#endif /* !ICOMPONENT_H_ */
