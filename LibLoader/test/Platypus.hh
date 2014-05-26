#ifndef _PLATYPUS_H_
#define _PLATYPUS_H_

#include "IAnimal.hh"

class Platypus : public IAnimal
{
public:
	void scream() const;
};

#endif