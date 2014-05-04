#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#define DECLSPEC __declspec(dllexport)

class IAnimal
{
public:
	virtual void scream() const = 0;
};

#endif