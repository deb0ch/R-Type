#ifndef ITASK_H_
# define ITASK_H_

class ITask
{
public:
  virtual void	run() = 0;
  virtual void	operator()() = 0;

  virtual	~ITask() {}
};

#endif /* !ITASK_H_ */
