
#include <ostream>
#include "Threads.hh"

Mutex	g_mutex;

class ClassTest
{
public:
	void	TestFunction(Any & arg);
	void	TestFunction2(Any & arg);
public:
	ClassTest() {}
	virtual ~ClassTest() {}

private:
	ClassTest(const ClassTest &);
	ClassTest &operator=(const ClassTest &);
protected:
  int	_arg;
};

void	ClassTest::TestFunction2(Any &arg)
{
	ScopedMutex toto(&g_mutex);
	std::string hey = "abcdefghijkabcdefghijkabcdefghijkabcdefghijk\n";
	for (size_t i = 0; i < 1000; i++)
	{
		for (int i = 0; i < hey.length(); ++i)
		{
			putchar(hey[i]);
		}
	}
}

void	ClassTest::TestFunction(Any & arg)
{
	std::ostringstream strstream;

	std::string	hey = "Hey ! Je suis le thread ";
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

int	main()
{
	ClassTest obj2Merde;
	ClassTest obj2Merdebis;
	ThreadPool<ClassTest> *pool = new ThreadPool<ClassTest>(4);
	Thread<ClassTest>	thread1;
	Thread<ClassTest>	thread2;
	Thread<ClassTest>	thread3;
	Thread<ClassTest>	thread4;
	int		toto1 = 42;
	int		toto2 = 84;

	thread1.start(Any(&toto1), &obj2Merde, &ClassTest::TestFunction2);
	thread2.start(Any(&toto2), &obj2Merdebis, &ClassTest::TestFunction2);
	thread3.start(Any(&toto1), &obj2Merdebis, &ClassTest::TestFunction2);
	thread4.start(Any(&toto2), &obj2Merdebis, &ClassTest::TestFunction2);
	thread1.wait();
	thread2.wait();
	thread3.wait();
	thread4.wait();
	getchar();
	return (0);
}
