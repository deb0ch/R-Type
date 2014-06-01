#ifndef ENTITYFILEEXCEPTION_H_
# define ENTITYFILEEXCEPTION_H_

# include	<string>

class EntityFileException : public std::exception
{
protected:
  std::string	_filename;
  std::string	_component;
  std::string	_message;
  unsigned int	_lineno;

public:
  EntityFileException(const std::string & message = "", unsigned int lineno = 0);
  ~EntityFileException();

  virtual const char*	what() const throw();
  void			setFilename(const std::string &);
  void			setComponent(const std::string &);
  void			setLineNo(unsigned int);
};

#endif /* !ENTITYFILEEXCEPTION_H_ */
