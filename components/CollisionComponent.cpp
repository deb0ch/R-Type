#include	<algorithm>

#include "CollisionComponent.hh"

CollisionComponent::CollisionComponent() : ASerializableComponent("CollisionComponent")
{}

CollisionComponent::~CollisionComponent()
{
  this->_collisionPoints.clear();
  this->_toCollide.clear();
  this->_toNotCollide.clear();
}

CollisionComponent::CollisionComponent(const CollisionComponent &e) : ASerializableComponent("CollisionComponent")
{
  this->operator=(e);
}

CollisionComponent	&CollisionComponent::operator=(const CollisionComponent &e)
{
  if (this != &e)
    {
      std::for_each(e._collisionPoints.begin(),
		    e._collisionPoints.end(),
		    [this] (CollisionPoint *cp) {
		      this->_collisionPoints.push_back(new CollisionPoint(*cp));
		    });
      this->_toCollide = e._toCollide;
      this->_toNotCollide = e._toNotCollide;
    }
  return (*this);
}

std::list<CollisionPoint *>	const &CollisionComponent::getCollisionPoints() const
{
  return (this->_collisionPoints);
}

CollisionComponent		*CollisionComponent::addCollisionPoint(CollisionPoint *point)
{
  this->_collisionPoints.push_front(point);
  return (this);
}

ASerializableComponent		*CollisionComponent::cloneSerializable() const
{
  return (new CollisionComponent(*this));
}

void				CollisionComponent::serialize(IBuffer &) const
{}

void				CollisionComponent::unserialize(IBuffer &)
{}

std::list<std::string>	const &CollisionComponent::getToCollide() const
{
  return (this->_toCollide);
}

std::list<std::string>	const &CollisionComponent::getToNotCollide() const
{
  return (this->_toNotCollide);
}

CollisionComponent	       *CollisionComponent::addToCollideItem(std::string const &item)
{
  this->_toCollide.push_back(item);
  return (this);
}

CollisionComponent	       *CollisionComponent::addNotToCollideItem(std::string const &item)
{
  this->_toNotCollide.push_front(item);
  return (this);
}

void	CollisionComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("toCollide=.+")))
    this->_toCollide.push_back(lastline.substr(10));
  else if (std::regex_match(lastline, std::regex("toNotCollide=.+")))
    this->_toNotCollide.push_back(lastline.substr(13));
  else if (std::regex_match(lastline, std::regex("collisionPoints=COMPONENT:CollisionPoint")))
    {
      CollisionPoint	*cp = new CollisionPoint();
      cp->deserializeFromFile(input);
      this->_collisionPoints.push_back(cp);
    }
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	CollisionComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  std::for_each(this->_collisionPoints.begin(), this->_collisionPoints.end(), [&output, indent](const CollisionPoint *cp)
		{
		  output << std::string(indent, '\t') << "collisionPoints=COMPONENT:" << cp->getType() << std::endl;
		  cp->serializeFromFile(output, indent + 1);
		  output << std::string(indent, '\t') << "!COMPONENT" << std::endl;
		});
  std::for_each(this->_toCollide.begin(), this->_toCollide.end(), [&output, indent](const std::string &s)
		{
		  output << std::string(indent, '\t') << "toCollide=" << s << std::endl;
		});
  std::for_each(this->_toNotCollide.begin(), this->_toNotCollide.end(), [&output, indent](const std::string &s)
		{
		  output << std::string(indent, '\t') << "toNotCollide=" << s << std::endl;
		});
}
