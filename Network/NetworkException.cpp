#include <sstream>
#include <cstring>
#include "NetworkException.hh"

void NetworkException::addError(const int error)
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

NetworkException::NetworkException(const std::string &info, const int error)
{
  this->_info = info;
  this->addError(error);
}

NetworkException::NetworkException(const std::string &info)
{
  this->_info = info;
}

const char*   NetworkException::what() const throw() {
  return (this->_info.c_str());
}
