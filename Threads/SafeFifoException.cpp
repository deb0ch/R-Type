#ifdef __linux__
# define _XOPEN_SOURCE 601
#endif /* !__linux__ */

#include "SafeFifoException.hh"

void SafeFifoException::addError(const int error)
{
  char buffer[512];
  std::string res;

  memset(buffer, 0, 512);
#ifdef _WIN32
  strerror_s(buffer, sizeof(buffer), error);
  this->_info += buffer;
#elif __linux__
  this->_info += strerror_r(error, buffer, sizeof(buffer));
#endif
}

/* Public Constructor */
SafeFifoException::SafeFifoException(const int error) {
  this->_info = "SafeFifoException : ";
  this->addError(error);
}

SafeFifoException::SafeFifoException(const std::string &info) {
  this->_info = "SafeFifoException : ";
  this->_info = info;
}

/* Methodes */
const char*   SafeFifoException::what() const throw() {
  return (this->_info.c_str());
}
