
#include <ostream>
#include "Threads.hh"

Mutex	g_mutex;

class PutainDeSaMere
{
public:
  void	fct2Merde(Any & arg);
public:
  PutainDeSaMere() {}
  virtual ~PutainDeSaMere() {}

private:
  PutainDeSaMere(const PutainDeSaMere &);
  PutainDeSaMere &operator=(const PutainDeSaMere &);
protected:
  int	_arg;
};

void	PutainDeSaMere::fct2Merde(Any & arg)
{
	std::ostringstream strstream;

	std::string		hey = "Hey ! Je suis le thread ";
	_arg = *arg.getValue<int>();
	strstream << hey << _arg << std::endl;
	hey = strstream.str();
	g_mutex.lock();
	for (size_t i = 0; i < 1000; i++)
	{
		for (int i = 0; i < hey.length(); ++i)
		{
			putchar(hey[i]);
		}
	}
	g_mutex.unlock();
}

int	main(int ac, char **av)
{
	PutainDeSaMere obj2Merde;
	PutainDeSaMere obj2Merdebis;
	Thread<PutainDeSaMere>	thread1;
	Thread<PutainDeSaMere>	thread2;
	int		toto1 = 42;
	int		toto2 = 84;

	thread1.start(Any(&toto1), &obj2Merde, &PutainDeSaMere::fct2Merde);
	thread2.start(Any(&toto2), &obj2Merdebis, &PutainDeSaMere::fct2Merde);
	thread1.wait();
	thread2.wait();
	getchar();
	return (0);
}
