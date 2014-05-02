#include <sstream>
#include "NetworkException.hh"

std::map<NetworkException::ERROR_TYPE, const std::string> NetworkException::_msg = {
  {NetworkException::NONE, "Exception : "},
  {NetworkException::TCP, "Socket TCP Exception : "},
  {NetworkException::UDP, "Socket UDP Exception : "}
};

NetworkException::NetworkException(const NetworkException::ERROR_TYPE type, const int error) {
  if (NetworkException::_msg.find(type) != NetworkException::_msg.end())
    this->_info = NetworkException::_msg[type];
  else
    this->_info = NetworkException::_msg[NONE];
  this->_info += strerror(error);
}

NetworkException::NetworkException(const NetworkException::ERROR_TYPE type, const std::string &info) {
  if (NetworkException::_msg.find(type) != NetworkException::_msg.end())
    this->_info = NetworkException::_msg[type];
  else
    this->_info = NetworkException::_msg[NONE];
  this->_info += info;
}

const char*   NetworkException::what() const throw() {
  return (this->_info.c_str());
}
