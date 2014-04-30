
#ifdef __linux__ 
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <iostream>

int	main()
{
	std::cout << "Hello world!" << std::endl;
#ifdef __linux__ 
	sleep(5);
#elif _WIN32
	Sleep(5000);
#endif
}