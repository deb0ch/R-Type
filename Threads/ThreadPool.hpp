#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <vector>
# include "IThread.hpp"
# include "Threads.hh"

template <typename T>
class ThreadPool
{
private :
  std::vector<Thread<T> *> pool;

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

public :
  ThreadPool(int nb_thread)
  {
    for (int i = 0; i < nb_thread; i++)
      {
	this->pool.push_back(new Thread<T>());
      }
  }

  void AddThreadToPool(Any arg, T* obj, void (T::*fct)(Any &))
  {
    this->pool.push_back(new Thread<T>());
    this->pool.back()->start(arg, obj, fct);
  }

  void StartPooling(Any arg, T* obj, void (T::*fct)(Any &))
  {
    for (unsigned int i = 0; i < this->pool.size(); i++)
      {
	this->pool[i]->start(arg, obj, fct);
      }
  }
};

#endif /* !THREADPOOL_H_ */
