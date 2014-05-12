#include <sstream>
#include <cstring>
#include "SelectException.hh"

SelectException::SelectException(const int error)
  : NetworkException("SelectException : ", error)
{}

SelectException::SelectException(const std::string &error)
  : NetworkException("SelectException : ", error)
{}
