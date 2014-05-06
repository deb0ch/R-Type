#ifndef IBUFFER_H_
# define IBUFFER_H_

# include <string>

class IBuffer
{
public:
  virtual ~IBuffer()
  {}
  virtual IBuffer &operator<<(const int &) = 0;
  virtual IBuffer &operator<<(const unsigned long &) = 0;
  virtual IBuffer &operator<<(const float &) = 0;
  virtual IBuffer &operator<<(const std::string &) = 0;
  virtual IBuffer &operator<<(const std::size_t &) = 0;
  virtual IBuffer &operator<<(const char &) = 0;

  virtual IBuffer &operator>>(int &) = 0;
  virtual IBuffer &operator>>(unsigned long &) = 0;
  virtual IBuffer &operator>>(float &) = 0;
  virtual IBuffer &operator>>(std::string &) = 0;
  virtual IBuffer &operator>>(std::size_t &) = 0;
  virtual IBuffer &operator>>(char &) = 0;

  virtual bool end() const = 0;
  virtual void rewind() = 0;
  virtual void reset() = 0;

protected:

};

#endif /* !IBUFFER_H_ */
