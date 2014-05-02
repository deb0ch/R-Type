#ifdef _SOCKET_FD_
#define _SOCKET_FD_

#ifdef _WIN32
typedef UINT_PTR SocketFD;
#elif __linux__
typedef int SocketFD;
#endif

#endif