#ifdef __linux__
	#define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "NetworkException.hh"

void NetworkException::addError(const int error)
{
  char buffer[512];

  memset(buffer, 0, 512);
#ifdef _WIN32
  strerror_s(buffer, sizeof(buffer), error);
  this->_info += buffer;
#elif __linux__
  this->_info += strerror_r(error, buffer, sizeof(buffer));
#endif
}

/* Public Constructor */
NetworkException::NetworkException(const int error) {
  this->_info = "NetworkException : ";
  this->addError(error);
}
NetworkException::NetworkException(const std::string &info) {
  this->_info = "NetworkException : ";
  this->_info += info;
}

/* Protected Constructor */
NetworkException::NetworkException(const std::string &prefix, const int error) {
  this->_info = prefix;
  this->addError(error);
}
NetworkException::NetworkException(const std::string &prefix, const std::string &error) {
  this->_info = prefix;
  this->_info += error;
}

/* Methodes */
const char*   NetworkException::what() const throw() {
  return (this->_info.c_str());
}
