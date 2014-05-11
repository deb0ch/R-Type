#ifndef		ACTIONCOMPONENT_H_
# define	ACTIONCOMPONENT_H_

# include	<map>
# include	<string>

# include	"AComponent.hpp"

class		ActionComponent : public AComponent<ActionComponent>
{
private:
  std::map<std::string, bool>	_actions;

public:
  ActionComponent();
  virtual ~ActionComponent();

  /**
   * @brief Checks if an action is active.
   */
  bool			isActive(const std::string &action) const;
  /**
   * @brief Add an possible action.
   */
  ActionComponent*	addAction(const std::string &);
  /**
   * @brief Activate or desactivate an action.
   */
  void			setAction(const std::string &, const bool status);
};

#endif /* !ACTIONCOMPONENT_H_ */
