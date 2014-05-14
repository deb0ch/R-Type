#ifndef TASK_H_
# define TASK_H_

# include "ITask.hh"

template <typename T>
class Task : public ITask
{
public:
  virtual void	run() { (_obj->*(_fct))(_arg); }
  virtual void	operator()() { (_obj->*(_fct))(_arg); }

		Task(T* obj, void (T::*fct)(Any), Any arg) : _obj(obj), _fct(fct), _arg(arg) {}
  virtual	~Task() {}

private:
		Task(const Task & other) = delete;
  Task &	operator=(const Task & other) = delete;

protected:
  T *		_obj;
  void		(T::*_fct)(Any);
  Any		_arg;
};

class CTask : public ITask
{
public:
  virtual void		run() { (*_task)(_arg); }
  virtual void		operator()() { (*_task)(_arg);; }

  CTask(void* (*_task)(void*), void* _arg);
  virtual		~CTask() {}

private:
  CTask();
  CTask(const CTask & other) = delete;
  CTask &	operator=(const CTask & other) = delete;

protected:
  void*			(*_task)(void*);
  void*			_arg;
};

#endif /* !TASK_H_ */
