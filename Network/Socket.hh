#ifndef _SOCKET_INCLUDE_H_
#define _SOCKET_INCLUDE_H_

#ifdef __linux__
	#include "USocketTCP.hh"
	#include "USocketUDP.hh"
#elif _WIN32
	#include "WSocketTCP.hh"
	#include "WSocketUDP.hh"
#endif

#endif /* !_SOCKET_INCLUDE_H_ */
