#include	<iostream>
#include	<list>

#include	"SFMLRenderSystem.hh"

#include	"SFMLSpriteComponent.hh"
#include	"CollisionComponent.hh"
#include	"ActionComponent.hh"

SFMLRenderSystem::SFMLRenderSystem()
: ASystem("SFMLRenderSystem")
{}

SFMLRenderSystem::~SFMLRenderSystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLRenderSystem::canProcess(Entity *entity)
{
	if (entity->hasComponent("SFMLSpriteComponent") && entity->hasComponent("Pos2DComponent"))
		return (true);
	return (false);
}

void		SFMLRenderSystem::displayCollision(Entity *entity)
{
	std::list<CollisionPoint *>	const &entityPoints = entity->getComponent<CollisionComponent>("CollisionComponent")->getCollisionPoints();
	Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
	Pos2DComponent	*posC;
	Box2DComponent	*boxC;

	for (auto it = entityPoints.begin(); it != entityPoints.end(); ++it)
	{
		posC = (*it)->getPos();
		boxC = (*it)->getBox();
		float	width = boxC->getWidth();
		float	height = boxC->getHeight();
		sf::RectangleShape rectangle(sf::Vector2f(width, height));
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setPosition(pos->getX() + posC->getX(), pos->getY() + posC->getY());
		rectangle.setOrigin(width / 2, height / 2);
		rectangle.setOutlineThickness(-3);
		rectangle.setOutlineColor(sf::Color(0, 250, 0));
		this->_window->draw(rectangle);
	}
}

void		SFMLRenderSystem::displayBox2D(float width, float height, Pos2DComponent *pos)
{
	sf::RectangleShape rectangle(sf::Vector2f(width, height));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOrigin(width / 2, height / 2);
	rectangle.setPosition(pos->getX(), pos->getY());
	rectangle.setOutlineThickness(-3);
	rectangle.setOutlineColor(sf::Color(250, 0, 0));
	this->_window->draw(rectangle);
}

void		SFMLRenderSystem::processEntity(Entity *entity, const float)
{
	SFMLSpriteComponent	*spriteComp = entity->getComponent<SFMLSpriteComponent>("SFMLSpriteComponent");
	Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
	Box2DComponent	*box = entity->getComponent<Box2DComponent>("Box2DComponent");
	ActionComponent	*action = entity->getComponent<ActionComponent>("ActionComponent");
	float			width;
	float			height;
	ImageLoader *imageLoader = this->_world->getSharedObject<ImageLoader>("imageLoader");

	if (!imageLoader)
		return; //TODO throw
	sf::Sprite *sprite = NULL;
	if (action != NULL)
	{
		if (action->isActive("UP") && spriteComp->hasAction("UP"))
			sprite = spriteComp->getSprite(*imageLoader, "UP");
		else if (action->isActive("DOWN") && spriteComp->hasAction("DOWN"))
			sprite = spriteComp->getSprite(*imageLoader, "DOWN");
	}
	width = (box) ? box->getWidth() : 0;
	height = (box) ? box->getHeight() : 0;
	if (debug)
	{
		displayBox2D(width, height, pos);
		if (entity->hasComponent("CollisionComponent"))
			displayCollision(entity);
	}
	if (sprite == NULL)
		sprite = spriteComp->getSprite(*imageLoader);
	if (sprite == NULL)
	  {
	    std::cout << "Sprite does not exist" << std::endl;
	    return;
	  }
	sprite->setPosition(pos->getX() - (width / 2), pos->getY() - (height / 2));
	if (box)
		sprite->setScale(width / sprite->getLocalBounds().width,
		height / sprite->getLocalBounds().height);
	this->_window->draw(*sprite);
	delete sprite;
}

void		SFMLRenderSystem::start()
{
	this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "EpicGradius");
	this->_window->setVerticalSyncEnabled(true);
	this->_world->setSharedObject("sfmlwindow", this->_window);
}

void		SFMLRenderSystem::beforeProcess()
{
	this->_window->clear();
}

void		SFMLRenderSystem::afterProcess()
{
	this->_window->display();
}
