#ifndef RANDOMINT_H_
# define RANDOMINT_H_

# include	<random>

class		RandomInt
{
public:
  static std::default_random_engine	seed;

  RandomInt()
  {}
  RandomInt(const RandomInt&)
  {}
  ~RandomInt()
  {}
  RandomInt&	operator=(const RandomInt&)
  {
    return (*this);
  }

  template <typename T>
  T		operator()(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) const
  {
    return (std::uniform_int_distribution<T>(min, max)(seed));
  }

};

#endif /* !RANDOMINT_H_ */
