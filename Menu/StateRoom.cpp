# include "Window.hh"
# include "INetworkRelay.hh"
# include "LockGuard.hpp"
# include "StateRoom.hh"
# include "Threads.hh"
# include "ClientRelay.hh"
# include "Any.hpp"
# include "StateGame.hh"
# include "RTException.hh"

StateRoom::StateRoom(sf::RenderWindow * window, World *world, sf::Music *music)
{
  this->_window = window;
  this->_world = world;
  this->init();
  this->_music = music;
}

StateRoom::~StateRoom()
{}

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
  this->_textboxRoom->setBorderColor(sf::Color(255, 255, 255, 160));
  this->_textboxRoom->setBorderSize(270, 45);
}

void	StateRoom::accessRoom()
{
  INetworkRelay *network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");

  if (network)
    {
      Remote *remote = NULL;

      if (this->_textboxRoom->getString() != "")
	this->_textboxRoom->setString("defaulte");
      if (!(remote = network->getRemote(0)))
	throw RTException("Invalid remote");

      IBuffer *buffer = network->getTCPBuffer();

      *buffer << static_cast<char>(INetworkRelay::CHANGE_ROOM_QUERY);
      *buffer << this->_textboxRoom->getString();
      remote->sendTCP(buffer);

      Thread<INetworkRelay> *thread = new Thread<INetworkRelay>();

      thread->start(network, &INetworkRelay::threadStart);

      while (42)
	{
	  LockVector<IBuffer *> &recv_buffer = remote->getRecvBufferTCP();
	  auto guard = create_lock(recv_buffer);

	  for (auto it = recv_buffer.begin(); it != recv_buffer.end();)
	    {
	      if (this->parsePacket(recv_buffer, it))
		return ;
	    }
	}
    }
  else
    {
      throw RTException("Invalid network");
    }
}

bool StateRoom::parsePacket(LockVector<IBuffer *> &vector, LockVector<IBuffer *>::iterator &it)
{
  char		packet_type;
  IBuffer	*buffer;
  std::string	msg;

  buffer = *it;
  buffer->rewind();
  *buffer >> packet_type;
  if (packet_type == INetworkRelay::CHANGE_ROOM_QUERY_YES
      || packet_type == INetworkRelay::CHANGE_ROOM_QUERY_NON)
    {
      if (packet_type == INetworkRelay::CHANGE_ROOM_QUERY_YES)
	{
	  return true;
	}
      else
	{
	  *buffer >> msg;
	  throw RTException(msg);
	}
      it = vector.erase(it);
      return true;
    }
  else
    ++it;
  return false;
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
	  manager.exit();
	  break ;

	case sf::Event::TextEntered:
	  if (event.text.unicode == 13)
	    {
	      this->_music->stop();
	      this->accessRoom();
	      manager.pushState(new StateGame(this->_world));
	    }
	  else if (event.text.unicode == 8)
	    this->_textboxRoom->removelastCharacter();
	  else
	    {
	      this->_textboxRoom->addCharacter(static_cast<char>(event.text.unicode));
	    }
	  break ;

	case sf::Event::MouseButtonPressed:
	  this->_music->stop();
	  this->accessRoom();
	  manager.pushState(new StateGame(this->_world));
	  return ;
	  break ;

	default:
	  break ;
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
