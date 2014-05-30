#include "CollisionPoint.hh"

CollisionPoint::CollisionPoint(float x, float y, float width, float height) : ACopyableComponent("CollisionPoint")
{
  this->_pos = new Pos2DComponent(x, y);
  this->_box = new Box2DComponent(width, height);
}

CollisionPoint::~CollisionPoint()
{
  delete this->_pos;
  delete this->_box;
}

CollisionPoint::CollisionPoint(const CollisionPoint &e) : ACopyableComponent("CollisionPoint")
{
  if (e._pos)
    this->_pos = new Pos2DComponent(*e._pos);
  else
    this->_pos = NULL;
  if (e._box)
    this->_box = new Box2DComponent(*e._box);
  else
    this->_pos = NULL;
}

CollisionPoint	&CollisionPoint::operator=(const CollisionPoint &e)
{
  if (this != &e)
    {
      if (e._pos)
	this->_pos = new Pos2DComponent(*e._pos);
      else
	this->_pos = NULL;
      if (e._box)
	this->_box = new Box2DComponent(*e._box);
      else
	this->_pos = NULL;
    }
  return (*this);
}

Pos2DComponent		*CollisionPoint::getPos() const
{
  return (this->_pos);
}

Box2DComponent		*CollisionPoint::getBox() const
{
  return (this->_box);
}

void		CollisionPoint::serialize(IBuffer &) const
{}

void		CollisionPoint::unserialize(IBuffer &)
{}

void	CollisionPoint::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("x=.+")))
    this->_pos->setX(std::stof(lastline.substr(2)));
  else if (std::regex_match(lastline, std::regex("y=.+")))
    this->_pos->setY(std::stof(lastline.substr(2)));
  else if (std::regex_match(lastline, std::regex("width=.+")))
    this->_box->setWidth(std::stof(lastline.substr(6)));
  else if (std::regex_match(lastline, std::regex("height=.+")))
    this->_box->setHeight(std::stof(lastline.substr(7)));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void		CollisionPoint::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "x=" << this->getPos()->getX() << std::endl;
  output << std::string(indent, '\t') << "y=" << this->getPos()->getY() << std::endl;
  output << std::string(indent, '\t') << "width=" << this->getBox()->getWidth() << std::endl;
  output << std::string(indent, '\t') << "height=" << this->getBox()->getHeight() << std::endl;
}
