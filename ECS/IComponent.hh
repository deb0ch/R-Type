#ifndef ICOMPONENT_H_
# define ICOMPONENT_H_

# include <string>

# if _WIN32
	#define DECLSPEC __declspec(dllexport)
# elif __linux__
	#define DECLSPEC
# endif

class		IComponent
{
public:
  virtual	~IComponent() {};

  virtual const std::string	&getType() const = 0;
  virtual IComponent		*clone() const = 0;
  virtual void			deserializeFromFile(std::ifstream &input) = 0;
  virtual void			serializeFromFile(std::ofstream &output, unsigned char indent) const = 0;
};

#endif /* !ICOMPONENT_H_ */
