#ifndef _LIBRARYLOADER_H_
#define _LIBRARYLOADER_H_

#include <string>
#include "ILibraryLoader.hh"

#pragma comment(lib, "ws2_32.lib")
/*
template <typename T>
class LibraryLoader : public ILibraryLoader<T>
{
public:
	T *getInstance(const std::string &path, const std::string &entry);
};
*/

class LibraryLoader : public ILibraryLoader
{
public:
	IAnimal *getInstance(const std::string &path, const std::string &entry);
};

#endif