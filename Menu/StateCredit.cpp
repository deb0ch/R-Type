#include "Window.hh"
#include "SFML/Window/WindowStyle.hpp"
#include "StateCredit.hh"
#include "StateManager.hh"

StateCredit::StateCredit(sf::RenderWindow *window)
{
	this->_window = window;
	this->init();
}

StateCredit::~StateCredit()
{}

void StateCredit::init()
{
	this->_background = NULL;

	sf::Texture *texture = new sf::Texture();
	if (texture->loadFromFile("Ressources/Images/credit.jpg"))
	{
		this->_background = new sf::Sprite();
		this->_background->setTexture(*texture, true);
		this->_background->setScale(WINDOW_WIDTH / this->_background->getLocalBounds().width,
			WINDOW_HEIGHT / this->_background->getLocalBounds().height);
	}
	this->_names.push_back(new SFMLTextBox(this->_window, 200, 100, false, 70));
	this->_names.back()->setString("credits");
	this->_names.back()->setColor(sf::Color(229, 8, 54));
	this->_names.push_back(new SFMLTextBox(this->_window, 50, 200, false));
	this->_names.back()->setString("davoin_b");
	this->_names.back()->setColor(sf::Color(229, 8, 54));
	this->_names.push_back(new SFMLTextBox(this->_window, 50, 250, false));
	this->_names.back()->setString("chauvo_t");
	this->_names.back()->setColor(sf::Color(229, 8, 54));
	this->_names.push_back(new SFMLTextBox(this->_window, 50, 300, false));
	this->_names.back()->setString("demess_p");
	this->_names.back()->setColor(sf::Color(229, 8, 54));
	this->_names.push_back(new SFMLTextBox(this->_window, 50, 350, false));
	this->_names.back()->setString("ouabde_r");
	this->_names.back()->setColor(sf::Color(229, 8, 54));
	this->_names.push_back(new SFMLTextBox(this->_window, 50, 400, false));
	this->_names.back()->setString("yalap_j");
	this->_names.back()->setColor(sf::Color(229, 8, 54));
	this->_names.push_back(new SFMLTextBox(this->_window, 50, 450, false));
	this->_names.back()->setString("taieb_t");
	this->_names.back()->setColor(sf::Color(229, 8, 54));
}

void StateCredit::update(StateManager& manager)
{
	sf::Event	event;
	while (this->_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->_window->close();
			manager.exit();
			break;

		case sf::Event::KeyPressed:
		case sf::Event::MouseButtonPressed:
			manager.popState();
			break;

		default:
			break;
		}
	}
}

void StateCredit::render(const Timer&)
{
	this->_window->clear();

	if (this->_background)
		this->_window->draw(*this->_background);

	for (unsigned int i = 0; i < this->_names.size(); i++)
	{
		this->_names[i]->draw();
	}
	this->_window->display();
}
