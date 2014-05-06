#include <sstream>
#include <cstring>
#include "TCPException.hh"

TCPException::TCPException(const int error)
  : NetworkException("TCPException : ", error)
{}

TCPException::TCPException(const std::string &info)
  : NetworkException("TCPException : " + info)
{}
