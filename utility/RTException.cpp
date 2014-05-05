#ifdef __linux__
	#define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "RTException.hh"

std::map<const std::string, std::string> RTException::_msg = {
	{ "__Exception__", "Exception : " }
};

void RTException::addError(const int error)
{
  char buffer[512];
  std::string res;

#ifdef _WIN32
  strerror_s(buffer, sizeof(buffer), error);
this->_info += buffer;
#elif __linux__
if (strerror_r(error, buffer, sizeof(buffer)) == 0)
  this->_info += buffer;
#endif
}

RTException::RTException(const std::string type, const int error,
				   const RTException::SEVERITY severity)
{
  this->_severity = severity;
  if (RTException::_msg.find(type) != RTException::_msg.end())
    this->_info = RTException::_msg[type];
  else
    this->_info = RTException::_msg["__Exception__"];
  this->addError(error);
}

RTException::RTException(const std::string type, const std::string &info,
				   const RTException::SEVERITY severity)
{
  this->_severity = severity;
  if (RTException::_msg.find(type) != RTException::_msg.end())
    this->_info = RTException::_msg[type];
  else
    this->_info = RTException::_msg["__Exception__"];
  this->_info += info;
}

void RTException::addClass(const std::string nameClass, const std::string msg) {
  RTException::_msg[nameClass] = msg + " : ";
}

const char *RTException::what() const throw() {
	return (this->_info.c_str());
}

const RTException::SEVERITY RTException::getSeverity() const {
  return this->_severity;
}
