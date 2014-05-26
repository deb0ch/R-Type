#include <sstream>
#include <cstring>
#include "UDPException.hh"

UDPException::UDPException(const int error)
  : NetworkException("UDPException : ", error)
{}

UDPException::UDPException(const std::string &error)
  : NetworkException("UDPException : ", error)
{}
