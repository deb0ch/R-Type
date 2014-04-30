template<class T>
class		VectorDeleter
{
public:
  void	operator()(T pointer)
  { delete pointer; }
};
