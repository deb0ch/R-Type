#ifdef __linux__
	#define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "LibLoaderException.hh"

void LibLoaderException::addError(const int error)
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

LibLoaderException::LibLoaderException(const int error)
{
  this->_info = "LibLoaderException : ";
  this->addError(error);
}

LibLoaderException::LibLoaderException(const std::string &info)
{
  this->_info = "LibLoaderException : ";
  this->_info += info;
}

const char*   LibLoaderException::what() const throw() {
  return (this->_info.c_str());
}
