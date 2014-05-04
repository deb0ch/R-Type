#include "ThreadException.hh"

std::map<ThreadException::ERROR_TYPE, const std::string> ThreadException::_msg =
  {
    { ThreadException::NONE, "Exception : " },
    { ThreadException::THREAD, "THREAD Exception : " },
    { ThreadException::MUTEX, "MUTEX Exception : " }
  };

void ThreadException::addError(const int error)
{
  char buffer[512];
  std::string res;

#ifdef _WIN32
  strerror_s(buffer, sizeof(buffer), error);
  this->_info += buffer;
#elif __linux__
  strerror_r(error, buffer, sizeof(buffer));
  this->_info += buffer;
#endif
}

ThreadException::ThreadException(const ThreadException::ERROR_TYPE type, const int error,
				   const ThreadException::SEVERITY severity)
{
  this->_severity = severity;
  if (ThreadException::_msg.find(type) != ThreadException::_msg.end())
    this->_info = ThreadException::_msg[type];
  else
    this->_info = ThreadException::_msg[NONE];
  this->addError(error);
}

ThreadException::ThreadException(const ThreadException::ERROR_TYPE type, const std::string &info,
				   const ThreadException::SEVERITY severity)
{
  this->_severity = severity;
  if (ThreadException::_msg.find(type) != ThreadException::_msg.end())
    this->_info = ThreadException::_msg[type];
  else
    this->_info = ThreadException::_msg[NONE];
  this->_info += info;
}

const char*   ThreadException::what() const throw() {
  return (this->_info.c_str());
}

const ThreadException::SEVERITY ThreadException::getSeverity() const {
  return this->_severity;
}
