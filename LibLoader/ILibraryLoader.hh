#ifndef __ILIBRARYLOADER_H_
#define __ILIBRARYLOADER_H_

#include <string>
#include "IAnimal.hh"
/*
template <typename T>
class ILibraryLoader
{
public:
	virtual T *getInstance(const std::string &path, const std::string &entry = "getInstance") = 0;
};
*/
class ILibraryLoader
{
public:
	virtual IAnimal *getInstance(const std::string &path, const std::string &entry = "getInstance") = 0;
};

#endif