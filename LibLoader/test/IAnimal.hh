#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#if _WIN32
	#define DECLSPEC __declspec(dllexport)
#elif __linux__
	#define DECLSPEC
#endif


class IAnimal
{
public:
	virtual void scream() const = 0;
	virtual ~IAnimal() {};
};

#endif