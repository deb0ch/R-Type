#ifdef _WIN32

# include "NetworkInitializer.hh"
# include "NetworkException.hh"

NetworkInitializer::NetworkInitializer()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
	if (iResult != 0)
	{
		throw NetworkException(WSAGetLastError());
	}
}

NetworkInitializer::~NetworkInitializer()
{
	WSACleanup();
}

#endif