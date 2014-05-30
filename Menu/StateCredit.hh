#ifndef STATECREDIT_H_
# define STATECREDIT_H_

#include	"IState.hh"
#include	"SFML/Graphics.hpp"
#include	"SFMLButton.hh"
#include	"SFMLTextBox.hh"

class StateCredit : public IState
{
private :
	StateCredit(const StateCredit &) = delete;
	StateCredit&	operator=(const StateCredit&) = delete;

public:
	StateCredit(sf::RenderWindow *window);
	virtual ~StateCredit();

	virtual void update(StateManager&);
	virtual void render(const Timer&);


protected:
	void init();

	sf::Sprite *_background;
	std::vector<SFMLTextBox *>_names;
	sf::RenderWindow *_window;
};

#endif /* !STATECREDIT_H_ */
