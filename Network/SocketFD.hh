# if defined(_WIN32)
typedef UINT_PTR SocketFD;
# elif defined(__linux__)
typedef int SocketFD;
# endif
