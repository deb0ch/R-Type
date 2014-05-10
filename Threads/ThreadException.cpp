#ifdef __linux__
# define _XOPEN_SOURCE 601
#endif /* !__linux__ */

#include "ThreadException.hh"

void ThreadException::addError(const int error)
{
  char buffer[512];
  std::string res;

  memset(buffer, 0, 512);
#ifdef _WIN32
  strerror_s(buffer, sizeof(buffer), error);
  this->_info += buffer;
#elif __linux__
  strerror_r(error, buffer, sizeof(buffer));
  this->_info += buffer;
#endif
}

/* Public Constructor */
ThreadException::ThreadException(const int error) {
  this->_info = "ThreadException : ";
  this->addError(error);
}

ThreadException::ThreadException(const std::string &info) {
  this->_info = "ThreadException : ";
  this->_info = info;
}

/* Methodes */
const char*   ThreadException::what() const throw() {
  return (this->_info.c_str());
}
