
#ifdef __linux__ 
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <iostream>

int	main()
{
	std::cout << "Hello world!" << std::endl;
	Sleep(5000);
}