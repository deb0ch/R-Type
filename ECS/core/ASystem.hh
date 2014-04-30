#ifndef ASYSTEM_H_
# define ASYSTEM_H_

# include		"ISystem.hh"

class			ASystem : public ISystem
{
public:
			ASystem(unsigned int type = _default_priority);
  virtual		~ASystem();

  virtual void		process(std::vector<Entity *>&);
  virtual unsigned int	getPriority() const;
private:
  unsigned int		_priority;
  static const int	_default_priority = 20;
};

#endif /* !ASYSTEM_H_ */
