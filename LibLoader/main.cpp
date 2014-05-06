#ifdef _WIN32
#include "WLibraryLoader.hpp"
#elif __linux__
# define _BSD_SOURCE
#include <unistd.h>
#include "ULibraryLoader.hpp"
#endif

#include "ILibraryLoader.hh"
#include "IAnimal.hh"
#include <iostream>


int main()
{
	ILibraryLoader<IAnimal> *loader = new LibraryLoader<IAnimal>();

	IAnimal *toto = loader->getInstance("test/libplatypus.so");
	if (toto)
		toto->scream();
	loader->clearLibrary("test/libplatypus.so");
	IAnimal *titi = loader->getInstance("test/libplatypus.so");
	if (titi)
		titi->scream();
	IAnimal *cheval = loader->getInstance("test/libplatypus.so");
	if (cheval)
		cheval->scream();
	IAnimal *tata = loader->getInstance("test/libarmadillo.so", "entrypoint");
	if (tata)
		tata->scream();
	loader->clearLibraries();
	IAnimal *poney = loader->getInstance("test/libplatypus.so");
	if (poney)
		poney->scream();
	IAnimal *chocolat = loader->getInstance("test/libarmadillo.so", "entrypoint");
	if (chocolat)
		chocolat->scream();
	#if _WIN32
	Sleep(50000);
	#elif __linux__
	usleep(50000);
	#endif
}
