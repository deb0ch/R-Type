#include "ILibraryLoader.hh"
#include "IAnimal.hh"
#include <iostream>
#ifdef _WIN32
	#include "WLibraryLoader.hpp"
#elif __linux__
	#include "ULibraryLoader.hpp"
#endif

int main()
{
	ILibraryLoader<IAnimal> *loader = new LibraryLoader<IAnimal>();

	IAnimal *toto = loader->getInstance("..\\test\\Debug\\platypus.dll");
	if (toto)
		toto->scream();
	loader->clearLibrary("..\\test\\Debug\\platypus.dll");
	IAnimal *titi = loader->getInstance("..\\test\\Debug\\platypus.dll");
	if (titi)
		titi->scream();
	IAnimal *cheval = loader->getInstance("..\\test\\Debug\\platypus.dll");
	if (cheval)
		cheval->scream();
	IAnimal *tata = loader->getInstance("..\\test\\Debug\\armadillo.dll", "entrypoint");
	if (tata)
		tata->scream();
	loader->clearLibraries();
	IAnimal *poney = loader->getInstance("..\\test\\Debug\\platypus.dll");
	if (poney)
		poney->scream();
	IAnimal *chocolat = loader->getInstance("..\\test\\Debug\\armadillo.dll", "entrypoint");
	if (chocolat)
		chocolat->scream();
	Sleep(50000);
}