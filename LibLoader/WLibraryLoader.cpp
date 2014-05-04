#include <Windows.h>
#include <iostream>
#include "WLibraryLoader.hh"
/*
template <typename T>
T *LibraryLoader<T>::getInstance(const std::string &path, const std::string &entry)
{
	T *(*create)();
	T *res = NULL;
	HINSTANCE Handle = LoadLibrary(path);
	if (Handle != INVALID_HANDLE_VALUE)
	{
		create = reinterpret_cast<T *(*)()>(GetProcAddress(Handle, entry));
		if (create)
		{
			res = create();
		}
		FreeLibrary(Handle);
	}
	return (res);
}
*/
IAnimal *LibraryLoader::getInstance(const std::string &path, const std::string &entry)
{
	IAnimal *(*instancier)();
	IAnimal *res = NULL;
	HINSTANCE Handle = LoadLibrary(path.c_str());
	if (Handle != INVALID_HANDLE_VALUE)
	{
		instancier = reinterpret_cast<IAnimal *(*)()>(GetProcAddress(Handle, entry.c_str()));
		if (instancier)
		{
			res = instancier();
			res->scream();
		}
		FreeLibrary(Handle);
	}
	return (res);
}