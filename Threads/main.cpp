
#include <unistd.h>
#include <ostream>
#include "Threads.hh"
#include "ThreadPool.hpp"

Mutex	g_mutex;

class ClassTest
{
public:
  void *	TestFunction(Any arg);
  void *	TestFunction2(Any arg);
public:
  ClassTest() {}
  virtual ~ClassTest() {}

private:
  ClassTest(const ClassTest &);
  ClassTest &operator=(const ClassTest &);
protected:
  int	_arg;
};

void *	ClassTest::TestFunction2(Any arg)
{
  ScopedMutex toto(&g_mutex);
  std::string hey = "abcdefghijkabcdefghijkabcdefghijkabcdefghijk\n";
  std::ostringstream strstream;

  strstream << *arg.getValue<int>();
  for (size_t i = 0; i < 10; i++)
    {
      std::cout << "thread [" << strstream.str() << "] ";
      for (unsigned int i = 0; i < hey.length(); ++i)
	putchar(hey[i]);
    }
}

void *	ClassTest::TestFunction(Any arg)
{
  std::ostringstream strstream;

  std::string	hey = "Hey ! Je suis le thread ";
  // sleep(0);
  std::cout << "Bouclinf !" << std::endl;
  while (42)
    {
      ;
    }
  std::cout << "Fin bounclinf" << std::endl;
  _arg = *arg.getValue<int>();
  strstream << hey << _arg << std::endl;
  hey = strstream.str();
  g_mutex.lock();
  for (size_t i = 0; i < 10; i++)
    {
      for (unsigned int i = 0; i < hey.length(); ++i)
	{
	  putchar(hey[i]);
	}
    }
  g_mutex.unlock();
}

int	main()
{
  ClassTest objTest;

  // ThreadPool	*pool = new ThreadPool(1);

  Thread<ClassTest> *thread = new Thread<ClassTest>;

  int		toto1 = 1;
  int		toto2 = 2;
  int		toto3 = 3;
  int		toto4 = 4;

  thread->start(&objTest, &ClassTest::TestFunction, Any(&toto4));
  // thread.wait();
  // pool->addTask(new Task<ClassTest>(&objTest, &ClassTest::TestFunction, Any(&toto1)));
  // pool.addTask(new TTask<ClassTest>(&objTest, &ClassTest::TestFunction, Any(toto2)));
  // pool.addTask(new TTask<ClassTest>(&objTest, &ClassTest::TestFunction2, Any(toto3)));
  // pool.addTask(new TTask<ClassTest>(&objTest, &ClassTest::TestFunction, Any(toto4)));
  // pool.addTask(new TTask<ClassTest>(&objTest, &ClassTest::TestFunction2, Any(toto1)));
  // pool.addTask(new TTask<ClassTest>(&objTest, &ClassTest::TestFunction, Any(toto2)));
  // pool->addTask(Any(&toto2), &objTest, &ClassTest::TestFunction2);
  // pool->addTask(Any(&toto3), &objTest, &ClassTest::TestFunction);
  // pool->addTask(Any(&toto4), &objTest, &ClassTest::TestFunction2);
  getchar();
  delete thread;
  std::cout << "delete on thread" << std::endl;
  getchar();
  return (0);
}
