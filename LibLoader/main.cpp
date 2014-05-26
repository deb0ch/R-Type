#include <string>

#ifdef _WIN32
	static const std::string pathLib = "../plugin/Debug/";
	static const std::string extension = ".dll";

	#include "WLibraryLoader.hpp"
#elif __linux__
	// # define _BSD_SOURCE
	static const std::string pathLib = "../plugin/lib";
	static const std::string extension = ".so";

	#include <unistd.h>
	#include "ULibraryLoader.hpp"
#endif

#include "ILibraryLoader.hh"
#include "IAnimal.hh"
#include <iostream>


int main()
{
	ILibraryLoader<IAnimal> *loader = new LibraryLoader<IAnimal>();

	IAnimal *toto = loader->getInstance(pathLib + std::string("platypus") + extension);
	if (toto)
		toto->scream();
	loader->clearLibrary(pathLib + std::string("platypus") + extension);
	IAnimal *titi = loader->getInstance(pathLib + std::string("platypus") + extension);
	if (titi)
		titi->scream();
	IAnimal *cheval = loader->getInstance(pathLib + std::string("platypus") + extension);
	if (cheval)
		cheval->scream();
	IAnimal *tata = loader->getInstance(pathLib + std::string("armadillo") + extension, "entrypoint");
	if (tata)
		tata->scream();
	loader->clearLibraries();
	IAnimal *poney = loader->getInstance(pathLib + std::string("platypus") + extension);
	if (poney)
		poney->scream();
	IAnimal *chocolat = loader->getInstance(pathLib + std::string("armadillo") + extension, "entrypoint");
	if (chocolat)
		chocolat->scream();
	getchar();
}
