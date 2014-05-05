#ifndef _LIBRARYLOADER_H_
#define _LIBRARYLOADER_H_

#include <string>
#include <Windows.h>
#include <iostream>
#include "ILibraryLoader.hh"

#pragma comment(lib, "ws2_32.lib")

template <typename T>
class LibraryLoader : public ILibraryLoader<T>
{
private:
	HINSTANCE last_Instance;

public:
	T *getInstance(const std::string &path, const std::string &entry);
	void clearLastLibrary();
};


template <typename T>
void		LibraryLoader<T>::clearLastLibrary()
{
	FreeLibrary(this->last_Instance);
}

template <typename T>
T *LibraryLoader<T>::getInstance(const std::string &path, const std::string &entry)
{
	T *(*instancier)();
	T *res = NULL;
	HINSTANCE Handle = LoadLibrary(path.c_str());
	if (Handle != INVALID_HANDLE_VALUE)
	{
		instancier = reinterpret_cast<T *(*)()>(GetProcAddress(Handle, entry.c_str()));
		if (instancier)
		{
			res = instancier();
		}
	}
	return (res);
}
#endif