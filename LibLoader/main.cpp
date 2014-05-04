#include "ILibraryLoader.hh"
#include "IAnimal.hh"
#include <Windows.h>
#include <iostream>

typedef IAnimal *(*getLibInstance)();
#pragma comment(lib, "ws2_32.lib")

int main()
{
	getLibInstance create;
	IAnimal *res = NULL;
	HINSTANCE Handle = LoadLibrary("..\\test\\Debug\\platypus.dll");
	if (Handle != INVALID_HANDLE_VALUE)
	{
		create = reinterpret_cast<getLibInstance>(GetProcAddress(Handle, "getInstance"));
		if (create)
		{
			res = create();
			res->scream();
		}
		//CloseHandle(Handle);
	}
	Handle = LoadLibrary("..\\test\\Debug\\armadillo.dll");
	if (Handle != INVALID_HANDLE_VALUE)
	{
		create = reinterpret_cast<getLibInstance>(GetProcAddress(Handle, "getInstance"));
		if (create)
		{
			res = create();
			res->scream();
		}
		//CloseHandle(Handle);
	}

	std::cout << "hey" << std::endl;
	Sleep(5000);
}