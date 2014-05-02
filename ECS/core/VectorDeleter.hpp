#ifndef VECTORDELETER_H_
# define VECTORDELETER_H_

template<class T>
class		VectorDeleter
{
public:
  void	operator()(T pointer)
  { delete pointer; }
};

#endif /* !VECTORDELETER_H_ */
