#include <iostream>
#include "Armadillo.hh"


void Armadillo::scream() const
{
	std::cout << "ARMADILLO !!!!" << std::endl;
}


extern "C"
{
	DECLSPEC Armadillo *getInstance()
	{
		return new Armadillo();
	}
}