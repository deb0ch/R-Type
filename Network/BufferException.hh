#ifndef BUFFEREXCEPTION_H_
# define BUFFEREXCEPTION_H_

# include <exception>
# include "IBuffer.hh"

class BufferException : public std::exception
{
public:
  BufferException() = delete;
  BufferException(IBuffer *, const std::string & = "") throw();
  virtual ~BufferException() throw();
  const char *what() const throw();
protected:
  const char *_str;
};

#endif /* !BUFFEREXCEPTION_H_ */
