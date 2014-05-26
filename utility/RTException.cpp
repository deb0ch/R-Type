#ifdef __linux__
	#define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "RTException.hh"

void RTException::addError(const int error)
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
RTException::RTException(const int error) {
  this->_info = "RTException : ";
  this->addError(error);
}

RTException::RTException(const std::string &info) {
  this->_info = "RTException : ";
  this->_info = info;
}

/* Protected Constructor */
RTException::RTException(const std::string &prefix, const int error) {
  this->_info = prefix;
  this->addError(error);
}

RTException::RTException(const std::string &prefix, const std::string &error) {
  this->_info = prefix;
  this->_info += error;
}

/* Methodes */
const char*   RTException::what() const throw() {
  return (this->_info.c_str());
}
