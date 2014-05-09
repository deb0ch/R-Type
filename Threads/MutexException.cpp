#ifdef __linux__
	#define _XOPEN_SOURCE 601
#endif

#include "MutexException.hh"

void MutexException::addError(const int error)
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
MutexException::MutexException(const int error) {
  this->_info = "MutexException : ";
  this->addError(error);
}
MutexException::MutexException(const std::string &info) {
  this->_info = "MutexException : ";
  this->_info = info;
}

/* Methodes */
const char*   MutexException::what() const throw() {
  return (this->_info.c_str());
}
