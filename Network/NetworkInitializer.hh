#ifndef NETWORK_INITIALIZER_H_
# define NETWORK_INITIALIZER_H_

#ifdef _WIN32
	#include <Windows.h>
#endif

class NetworkInitializer
{
private:
	#ifdef _WIN32
		WSADATA wsaData;
	#endif

private:
	NetworkInitializer(const NetworkInitializer &) = delete;
	NetworkInitializer &operator=(const NetworkInitializer &) = delete;

public:
	NetworkInitializer();
	virtual ~NetworkInitializer();
};

#endif /* !NETWORK_INITIALIZER_H_ */