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
	loader->clearLastLibrary();
	IAnimal *tata = loader->getInstance("..\\test\\Debug\\armadillo.dll", "entrypoint");
	if (tata)
		tata->scream();
	loader->clearLastLibrary();
	Sleep(5000);
}