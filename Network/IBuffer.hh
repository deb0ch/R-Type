#ifndef IBUFFER_H_
# define IBUFFER_H_

# include <string>

class IBuffer
{
public:
  virtual ~IBuffer()
  {}
  virtual IBuffer &operator<<(const int &) = 0;
  virtual IBuffer &operator<<(const unsigned int &) = 0;
  virtual IBuffer &operator<<(const unsigned long &) = 0;
  virtual IBuffer &operator<<(const float &) = 0;
  virtual IBuffer &operator<<(const std::string &) = 0;
  virtual IBuffer &operator<<(const char &) = 0;

  virtual IBuffer &operator>>(int &) = 0;
  virtual IBuffer &operator>>(unsigned int &) = 0;
  virtual IBuffer &operator>>(unsigned long &) = 0;
  virtual IBuffer &operator>>(float &) = 0;
  virtual IBuffer &operator>>(std::string &) = 0;
  virtual IBuffer &operator>>(char &) = 0;

  virtual bool			end() const = 0;
  virtual void			rewind() = 0;
  virtual void			gotoEnd() = 0;
  virtual void			reset() = 0;
  virtual const char		*getBuffer() const = 0;
  virtual char			*getBuffer() = 0;
  virtual unsigned int		getLength() const = 0;
  virtual void			setLength(unsigned int) = 0;
  virtual unsigned int		getRemainingLength() const = 0;
  virtual unsigned int		getMaxSize() const = 0;
  virtual unsigned int		getPosition() const = 0;
  virtual void			setPosition(unsigned int) = 0;
  virtual IBuffer		&operator=(const IBuffer &) = 0;
  virtual unsigned int		getOffset() const = 0;
  virtual void			addOffset(int) = 0;
protected:

};

#endif /* !IBUFFER_H_ */
