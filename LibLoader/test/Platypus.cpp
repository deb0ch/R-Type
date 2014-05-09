#include <iostream>
#include "Platypus.hh"


void Platypus::scream() const
{
	std::cout << "PLATYPUS !!!!" << std::endl;
}


extern "C"
{
	DECLSPEC Platypus *getInstance()
	{
		return new Platypus();
	}
}