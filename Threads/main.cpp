
#include <ostream>
#include <unistd.h>
#include "Threads.hh"
#include "ThreadPool.hpp"

Mutex	g_mutex;

class ClassTest
{
public:
  void	TestFunction(Any & arg);
  void	TestFunction2(Any & arg);
  void	toto(Any & arg);
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
  std::string hey = "abcdefghijkabcdefghijkabcdefghijkabcdefghijk\n";
  std::ostringstream strstream;

  strstream << *arg.getValue<int>();
  for (size_t i = 0; i < 2; i++)
    {
      std::cout << "thread [" << strstream.str() << "] ";
      for (unsigned int i = 0; i < hey.length(); ++i)
	putchar(hey[i]);
    }
}

void	ClassTest::TestFunction(Any & arg)
{
  std::ostringstream strstream;

  std::string	hey = "Hey ! Je suis le thread ";
  _arg = *arg.getValue<int>();
  strstream << hey << _arg << std::endl;
  hey = strstream.str();
  for (size_t i = 0; i < 10; i++)
    {
      for (unsigned int i = 0; i < hey.length(); ++i)
	{
	  putchar(hey[i]);
	}
      usleep(500000);
    }
}

int	main()
{
  ClassTest objTest;

  ThreadPool<ClassTest> *pool = new ThreadPool<ClassTest>(2);

  int		toto1 = 1;
  int		toto2 = 2;
  int		toto3 = 3;
  int		toto4 = 4;

  pool->addTask(Any(&toto1), &objTest, &ClassTest::TestFunction);
  pool->addTask(Any(&toto2), &objTest, &ClassTest::TestFunction2);
  pool->addTask(Any(&toto3), &objTest, &ClassTest::TestFunction);
  pool->addTask(Any(&toto4), &objTest, &ClassTest::TestFunction2);
  sleep(2);

  return (0);
}
