#ifndef THREADPOOL_H_
# define THREADPOOL_H_

#include <vector>
#include "IThread.hpp"
#include "SafeFifo.hpp"

template <typename T>
class ThreadPool
{
public :

  ThreadPool(unsigned int nbThread) {
    Thread<T> *thread;
    this->_nbThread = nbThread;
    for (unsigned int i = 0; i < nbThread; i++) {
	this->_pool.push_back(new Thread<T>());
      }
    this->StartPooling();
  }

  void startPooling(Any arg, T* obj, void (T::*fct)(Any &)) {
    for (unsigned int i = 0; i < this->_pool.size(); i++) {
	this->_pool[i]->start(i, this, run);
      }
  }

  void addTask(Any arg, T* obj, void (T::*fct)(Any &)) {
    Container *container = new Container();
    container->arg = arg;
    container->obj = obj;
    container->fct = fct;
    this->_task.push(container);
    //Envoi broacast a tous les thread via les variable conditionnelle
  }

  void	run(unsigned int count) {
    Container *toto;

    while (1) {
      // cond var wait
      if ((toto = this->_task.getNext()) != NULL) {
	this->_pool[count]->start(toto);
      }
    }
  }

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

private :
  struct Container
  {
    T *obj;
    void (T::*fct)(Any &);
    Any arg;
  };

  SafeFifo<Container *> _task;
  std::vector<Thread<T> *> _pool;
  unsigned int _nbThread;

};

#endif /* !THREADPOOL_H_ */
