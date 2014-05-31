#include <tuple>
#include "SFMLRenderSystem.hh"
#include "QuadTree.hh"

QuadTree::QuadTree(World *world, std::vector<Entity *> const &entities, float x, float y, float width, float height, int maxEntities, int depth)
{
  this->_world = world;
  this->_x = x;
  this->_y = y;
  this->_width = width;
  this->_height = height;
  this->maxEntities = maxEntities;
  for (auto it = entities.begin(); it != entities.end(); ++it)
    {
      if ((*it)->hasComponent("CollisionComponent") &&
	this->isInBlock((*it)->getComponent<Pos2DComponent>("Pos2DComponent"),
			(*it)->getComponent<Box2DComponent>("Box2DComponent")))
	this->Entities.push_back(*it);
    }
  if (depth > 0 && this->Entities.size() > this->maxEntities)
    {
      this->NorthWestBlock = new QuadTree(this->_world, this->Entities, x, y, width / 2, height / 2, maxEntities, depth - 1);
      this->NorthEastBlock = new QuadTree(this->_world, this->Entities, x + (width / 2), y, width / 2, height / 2, maxEntities, depth - 1);
      this->SouthWestBlock = new QuadTree(this->_world, this->Entities, x, y + (height / 2), width / 2, height / 2, maxEntities, depth - 1);
      this->SouthEastBlock = new QuadTree(this->_world, this->Entities, x + (width / 2), y + (height / 2), width / 2, height / 2, maxEntities, depth - 1);
    }
  else
    {
      this->NorthWestBlock = NULL;
      this->NorthEastBlock = NULL;
      this->SouthWestBlock = NULL;
      this->SouthEastBlock = NULL;
    }
  if (DEBUG)
    this->DrawDebug();
}

QuadTree::~QuadTree()
{
  if (this->NorthWestBlock != NULL)
    {
      delete this->NorthWestBlock;
      delete this->NorthEastBlock;
      delete this->SouthWestBlock;
      delete this->SouthEastBlock;
    }
}

void	QuadTree::DrawDebug()
{
  sf::RenderWindow	*_window = this->_world->getSharedObject<sf::RenderWindow>("sfmlwindow");
  sf::RectangleShape rectangle(sf::Vector2f(this->_width, this->_height));

  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setPosition(this->_x, this->_y);
  rectangle.setOutlineThickness(-2);
  rectangle.setOutlineColor(sf::Color(250, 250, 210));
  _window->draw(rectangle);
}

static bool	touchingTest(std::tuple<float, float, float, float> t1, std::tuple<float, float, float, float> t2)
{
  float inner_left;
  float inner_right;
  float inner_top;
  float inner_bot;

  inner_left = (std::max)(std::get<0>(t1) - (std::get<2>(t1) / 2.f),
			  std::get<0>(t2) - (std::get<2>(t2) / 2.f));
  inner_right = (std::min)(std::get<0>(t1) + (std::get<2>(t1) / 2.f),
			   std::get<0>(t2) + (std::get<2>(t2) / 2.f));
  inner_top = (std::max)(std::get<1>(t1) - (std::get<3>(t1) / 2.f),
			 std::get<1>(t2) - (std::get<3>(t2) / 2.f));
  inner_bot = (std::min)(std::get<1>(t1) + (std::get<3>(t1) / 2.f),
			 std::get<1>(t2) + (std::get<3>(t2) / 2.f));
  return ((inner_left < inner_right) && (inner_top < inner_bot));
}

bool	QuadTree::isInBlock(Pos2DComponent *pos, Box2DComponent *box) const
{
  if (!pos || !box)
    return (false);
  return (touchingTest(std::make_tuple(pos->getX(), pos->getY(), box->getWidth(), box->getHeight()),
		       std::make_tuple(this->_x + this->_width / 2.f, this->_y + this->_height / 2.f, this->_width, this->_height)));
}

std::vector<Entity *> const &QuadTree::findTree(Entity *entity)
{
  Pos2DComponent	*pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  Box2DComponent	*box = entity->getComponent<Box2DComponent>("Box2DComponent");
  std::vector<Entity *>	tmp;

  if (!this->NorthWestBlock)
    return (this->Entities);
  if (touchingTest(std::make_tuple(pos->getX(), pos->getY(), box->getWidth(), box->getHeight()),
		   std::make_tuple((this->_x) + this->_width / 2, this->_y + this->_height / 2, this->_width / 2, this->_height / 2)))
    {
      tmp = this->NorthWestBlock->findTree(entity);
      this->EntitiesRet.reserve(this->Entities.size() + tmp.size());
      this->EntitiesRet.insert(this->EntitiesRet.end(), tmp.begin(), tmp.end());
    }
  if (touchingTest(std::make_tuple(pos->getX(), pos->getY(), box->getWidth(), box->getHeight()),
  		   std::make_tuple((this->_x + (this->_width / 2)) + this->_width / 2, this->_y + this->_height / 2, this->_width / 2, this->_height / 2)))
    {
      tmp = this->NorthEastBlock->findTree(entity);
      this->EntitiesRet.reserve(this->Entities.size() + tmp.size());
      this->EntitiesRet.insert(this->EntitiesRet.end(), tmp.begin(), tmp.end());
    }
  if (touchingTest(std::make_tuple(pos->getX(), pos->getY(), box->getWidth(), box->getHeight()),
  		   std::make_tuple((this->_x) + this->_width / 2, (this->_y + (this->_height / 2)) + this->_height / 2, this->_width / 2, this->_height / 2)))
    {
      tmp = this->SouthWestBlock->findTree(entity);
      this->EntitiesRet.reserve(this->Entities.size() + tmp.size());
      this->EntitiesRet.insert(this->EntitiesRet.end(), tmp.begin(), tmp.end());
    }
  if (touchingTest(std::make_tuple(pos->getX(), pos->getY(), box->getWidth(), box->getHeight()),
  		   std::make_tuple((this->_x + (this->_width / 2)) + this->_width / 2, (this->_y + (this->_height / 2)) + this->_height / 2, this->_width / 2, this->_height / 2)))
    {
      tmp = this->SouthEastBlock->findTree(entity);
      this->EntitiesRet.reserve(this->Entities.size() + tmp.size());
      this->EntitiesRet.insert(this->EntitiesRet.end(), tmp.begin(), tmp.end());
    }
  return (this->EntitiesRet);
}

std::vector<Entity *> const &QuadTree::getEntities() const
{
  return (this->Entities);
}
