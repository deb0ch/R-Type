#ifndef		ACTIONCOMPONENT_H_
# define	ACTIONCOMPONENT_H_

# include	<map>
# include	<string>

# include	"ACopyableComponent.hpp"

class		ActionComponent : public ACopyableComponent<ActionComponent>
{
private:
  std::map<std::string, bool>	_actions;
  std::map<std::string, bool>	_actions_changed;

public:
  ActionComponent();
  virtual ~ActionComponent();

  /**
   * @brief Checks if an action is active.
   */
  bool			isActive(const std::string &action) const;
  /**
   * @brief Checks if an action has changed.
   */
  bool			hasChanged(const std::string &) const;
  /**
   * @brief Reset change
   */
  void			resetChange(const std::string &);
  /**
   * @brief Add an possible action.
   */
  ActionComponent*	addAction(const std::string &);
  /**
   * @brief Activate or desactivate an action.
   */
  void			setAction(const std::string &, const bool status);

  void			serialize(IBuffer &) const;
  void			unserialize(IBuffer &);
};

#endif /* !ACTIONCOMPONENT_H_ */
