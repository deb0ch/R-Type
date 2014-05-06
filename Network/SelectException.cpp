#include <sstream>
#include <cstring>
#include "SelectException.hh"

SelectException::SelectException(const int error)
  : NetworkException("SelectException : ", error)
{}

SelectException::SelectException(const std::string &info)
  : NetworkException("SelectException : " + info)
{}
