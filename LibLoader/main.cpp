#ifdef _WIN32
#define PATHLIB "..\\plugin\\Debug\\"
#define EXTENSION ".dll"
#include "WLibraryLoader.hpp"
#elif __linux__
# define _BSD_SOURCE
#define EXTENSION ".so"
#define PATHLIB "../Plugin/lib"
#include <unistd.h>
#include "ULibraryLoader.hpp"
#endif

#include "ILibraryLoader.hh"
#include "IAnimal.hh"
#include <iostream>


int main()
{
	ILibraryLoader<IAnimal> *loader = new LibraryLoader<IAnimal>();

	IAnimal *toto = loader->getInstance(PATHLIB + std::string("platypus") + EXTENSION);
	if (toto)
		toto->scream();
	loader->clearLibrary(PATHLIB + std::string("platypus") + EXTENSION);
	IAnimal *titi = loader->getInstance(PATHLIB + std::string("platypus") + EXTENSION);
	if (titi)
		titi->scream();
	IAnimal *cheval = loader->getInstance(PATHLIB + std::string("platypus") + EXTENSION);
	if (cheval)
		cheval->scream();
	IAnimal *tata = loader->getInstance(PATHLIB + std::string("armadillo") + EXTENSION, "entrypoint");
	if (tata)
		tata->scream();
	loader->clearLibraries();
	IAnimal *poney = loader->getInstance(PATHLIB + std::string("platypus") + EXTENSION);
	if (poney)
		poney->scream();
	IAnimal *chocolat = loader->getInstance(PATHLIB + std::string("armadillo") + EXTENSION, "entrypoint");
	if (chocolat)
		chocolat->scream();
#if _WIN32
	Sleep(50000);
#elif __linux__
	usleep(50000);
#endif
}
