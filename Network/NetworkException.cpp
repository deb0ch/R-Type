#include <sstream>
#include <cstring>
#include "NetworkException.hh"

std::map<NetworkException::ERROR_TYPE, const std::string> NetworkException::_msg = {
	{ NetworkException::NONE, "Exception : " },
	{ NetworkException::TCP, "Socket TCP Exception : " },
	{ NetworkException::UDP, "Socket UDP Exception : " }
};

void NetworkException::addError(const int error)
{
	char buffer[64];
	std::string res;

#ifdef _WIN32
	strerror_s(buffer, sizeof(buffer), error);
	this->_info += buffer;
#elif __linux__
	strerror_r(error, buffer, sizeof(buffer));
	this->_info += buffer;
#endif
}

NetworkException::NetworkException(const NetworkException::ERROR_TYPE type, const int error)
{
	if (NetworkException::_msg.find(type) != NetworkException::_msg.end())
		this->_info = NetworkException::_msg[type];
	else
		this->_info = NetworkException::_msg[NONE];
	this->addError(error);
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
