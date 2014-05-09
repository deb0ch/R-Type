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
  strerror_r(error, buffer, sizeof(buffer));
  this->_info += buffer;
#endif
}


RTException::RTException(const int error, const std::string &prefix)
{
  this->_info = prefix;
  this->addError(error);
}

RTException::RTException(const std::string &error, const std::string &prefix)
{
  this->_info = prefix;
  this->_info += error;
}

const char *RTException::what() const throw() {
	return (this->_info.c_str());
}
