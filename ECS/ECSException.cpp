#ifdef __linux__
	#define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "ECSException.hh"

void ECSException::addError(const int error)
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
ECSException::ECSException(const int error)
{
  this->_info = "ECSException : ";
  this->addError(error);
}

ECSException::ECSException(const std::string &info)
{
  this->_info = "ECSException : ";
  this->_info = info;
}

ECSException::ECSException(const std::string &prefix, const int error)
{
  this->_info = "ECSException : ";
  this->_info += prefix;
  this->addError(error);
}

ECSException::ECSException(const std::string &prefix, const std::string &error)
{
  this->_info = "ECSException : ";
  this->_info += prefix;
  this->_info += error;
}

/* Methodes */
const char*   ECSException::what() const throw()
{
  return (this->_info.c_str());
}
