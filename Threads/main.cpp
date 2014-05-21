#ifdef __linux__
# include <unistd.h>
#endif /* !__linux__ */
#include <ostream>
#include "Threads.hh"
#include "ThreadPool.hpp"

Mutex	g_mutex;

class ClassTest
{
public:
  void 	TestFunction(Any arg);
  void 	TestFunction2(Any arg);
public:
  ClassTest() {}
  virtual ~ClassTest() {}

private:
  ClassTest(const ClassTest &);
  ClassTest &operator=(const ClassTest &);
protected:
  int	_arg;
};

void 	ClassTest::TestFunction2(Any arg) {
  ScopedMutex p(&g_mutex);
  std::string hey = "abcdefghijkabcdefghijkabcdefghijkabcdefghijk\n";
  std::ostringstream strstream;

  strstream << *arg.getValue<int>();
  for (size_t i = 0; i < 1; i++)
    {
      std::cout << "thread [" << strstream.str() << "] ";
      for (unsigned int i = 0; i < hey.length(); ++i)
	putchar(hey[i]);
    }
}

void 	ClassTest::TestFunction(Any arg)
{
  ScopedMutex p(&g_mutex);
  std::ostringstream strstream;

  std::string	hey = "Hey ! Je suis le thread ";
  _arg = *arg.getValue<int>();
  strstream << hey << _arg ;
  hey = strstream.str();
  for (size_t i = 0; i < 1; ++i) {
    std::cout << hey << std::endl;
  }
}

int	main()
{
  ClassTest objTest;

  ThreadPool	*pool = new ThreadPool(5);

  int		toto1 = 1;
  int		toto2 = 2;
  int		toto3 = 3;
  int		toto4 = 4;

  for (int i = 0; i < 100; ++i)
    {
      pool->addTask(new Task<ClassTest>(&objTest, &ClassTest::TestFunction, Any(&toto1)));
      pool->addTask(new Task<ClassTest>(&objTest, &ClassTest::TestFunction2, Any(&toto2)));
      pool->addTask(new Task<ClassTest>(&objTest, &ClassTest::TestFunction, Any(&toto3)));
      pool->addTask(new Task<ClassTest>(&objTest, &ClassTest::TestFunction2, Any(&toto4)));
    }
  delete pool;
  return (0);
}
