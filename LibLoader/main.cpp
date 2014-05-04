#include "ILibraryLoader.hh"
#include "IAnimal.hh"
#include <Windows.h>
#include <iostream>
#include "WLibraryLoader.hh"

int main()
{
	//ILibraryLoader<IAnimal *> *loader = new LibraryLoader<IAnimal *>();
	ILibraryLoader *loader = new LibraryLoader();

	IAnimal *toto = loader->getInstance("..\\test\\Debug\\platypus.dll");
	if (toto)
		toto->scream();
	/*
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
		FreeLibrary(Handle);
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
		FreeLibrary(Handle);
	}
	*/
	std::cout << "hey" << std::endl;
	Sleep(5000);
}