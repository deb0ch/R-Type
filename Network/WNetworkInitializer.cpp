#ifdef _WIN32

# include "NetworkInitializer.hh"
# include "NetworkException.hh"

NetworkInitializer::NetworkInitializer()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
	if (iResult != 0)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::SEVERITY::S_ERROR);
	}
}

NetworkInitializer::~NetworkInitializer()
{
	WSACleanup();
}

#endif