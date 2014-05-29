#include	"Window.hh"
#include	"StateRoom.hh"
#include	"StateGame.hh"

StateRoom::StateRoom(sf::RenderWindow * window, World *world, const std::string &ipaddress)
: _window(window), _ipAddress(ipaddress), _world(world)
{
	this->init();
}

StateRoom::~StateRoom()
{
}

void	StateRoom::init()
{
	this->_background = NULL;
	sf::Texture *texture = new sf::Texture();
	if (texture->loadFromFile("Ressources/Images/rooms.jpg"))
	{
		this->_background = new sf::Sprite();
		this->_background->setTexture(*texture, true);
		this->_background->setScale(WINDOW_WIDTH / this->_background->getLocalBounds().width,
			WINDOW_HEIGHT / this->_background->getLocalBounds().height);
	}
	this->_serverRooms = new SFMLTextBox(this->_window, 5, 545, false, 40, 25);
	this->_serverRooms->setString("select a room : ");
	this->_serverRooms->setColor(sf::Color(150, 15, 229));

	this->_textboxRoom = new SFMLTextBox(this->_window, 350, 545, true, 40, 8);
	this->_textboxRoom->setColor(sf::Color(100, 15, 229));
	this->_textboxRoom->setBorderOutLineColor(sf::Color(150, 15, 250, 200));
	this->_textboxRoom->setBorderColor(sf::Color::Color(255, 255, 255, 160));
	this->_textboxRoom->setBorderSize(270, 45);
}

void	StateRoom::update(StateManager& manager)
{
	sf::Event	event;
	while (this->_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->_window->close();
			break;

		case sf::Event::TextEntered:
			if (event.text.unicode == 13)
				manager.pushState(new StateGame(this->_world, this->_ipAddress));
			else if (event.text.unicode == 8)
				this->_textboxRoom->removelastCharacter();
			else
			{
				this->_textboxRoom->addCharacter(static_cast<char>(event.text.unicode));
			}
			break;

		case sf::Event::MouseButtonPressed:
			manager.pushState(new StateGame(this->_world, this->_ipAddress));
			return;

		default:
			break;
		}
	}

}

void StateRoom::render(const Timer&)
{
	this->_window->clear();

	if (this->_background)
		this->_window->draw(*this->_background);
	this->_serverRooms->draw();
	this->_textboxRoom->draw();
	this->_window->display();
}