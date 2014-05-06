#ifndef __ARMADILLO_H__
#define __ARMADILLO_H__

#include "IAnimal.hh"

class Armadillo : public IAnimal
{
public:
	void scream() const;
};

#endif