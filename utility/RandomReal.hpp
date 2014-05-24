#ifndef RANDOMREAL_H_
# define RANDOMREAL_H_

# include	<random>

class		RandomReal
{
public:
  static std::default_random_engine	seed;

  RandomReal()
  {}
  RandomReal(const RandomReal&)
  {}
  ~RandomReal()
  {}
  RandomReal&	operator=(const RandomReal&)
  {
    return (*this);
  }

  template <typename T>
  T		operator()(T min = (std::numeric_limits<T>::min)(), T max = (std::numeric_limits<T>::max)()) const
  {
    return (std::uniform_real_distribution<T>(min, max)(seed));
  }

};

#endif /* !RANDOMREAL_H_ */
