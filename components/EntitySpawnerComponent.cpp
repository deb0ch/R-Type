#include	"EntitySpawnerComponent.hh"

#include	"EntityFactory.hpp"
#include	"RandomInt.hpp"
#include	"RandomReal.hpp"

//----- ----- Constructors ----- ----- //
EntitySpawnerComponent::EntitySpawnerComponent(std::vector<std::string> entities,
					       std::vector<std::string> components,
					       unsigned long nb,
					       unsigned long delay,
					       std::pair<float, float> min_pos,
					       std::pair<float, float> max_pos,
					       bool random,
					       bool abs)
						   : ACopyableComponent("EntitySpawnerComponent"),
    _entities(entities),
    _components(components),
    _nb(nb),
    _delay(delay),
    _min_pos(min_pos),
    _max_pos(max_pos),
    _random(random),
    _abs(abs)
{
  this->_next = 0;
  this->_active = true;
  this->_counter = 0;
  this->_tick = 0;
}

//----- ----- Destructor ----- ----- //
EntitySpawnerComponent::~EntitySpawnerComponent()
{}

//----- ----- Operators ----- ----- //
//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
void			EntitySpawnerComponent::setActive(bool active)
{
  this->_active = active;
}
//----- ----- Methods ----- ----- //
Entity			*EntitySpawnerComponent::spawnEntity(EntityFactory *facto, const Pos2DComponent *pos)
{
  Entity		*res = NULL;
  Pos2DComponent	*res_pos = NULL;

  if (this->_tick < this->_delay)
    return ((Entity *) (0 * ++this->_tick));

  if (!this->_active ||
      (this->_nb > 0 && this->_counter >= _nb) ||
      this->_entities.size() == 0)
    return (NULL);

  if (this->_tick >= this->_delay)
    this->_tick = 0;

  if (facto)
    res = facto->create(this->_entities[this->_next]);
  if (!this->_random)
    {
      ++this->_next;
      if (this->_next >= this->_entities.size())
	this->_next = 0;
    }
  else
    this->_next = RandomInt().operator() <unsigned long>(0, this->_entities.size() - 1);

  if (!res)
    return (NULL);
  res_pos = res->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!res_pos)
    {
      res_pos = new Pos2DComponent(0, 0);
      res->addComponent(res_pos);
    }
  res_pos->setX(0);
  res_pos->setY(0);
  if (!this->_abs && pos)
    {
      res_pos->setX(pos->getX());
      res_pos->setY(pos->getY());
    }
  res_pos->setX(res_pos->getX() + RandomReal()(this->_min_pos.first, this->_max_pos.first));
  res_pos->setY(res_pos->getY() + RandomReal()(this->_min_pos.second, this->_max_pos.second));

  ++this->_counter;
  return (res);
}

void			EntitySpawnerComponent::serialize(IBuffer &) const
{}

void			EntitySpawnerComponent::unserialize(IBuffer &)
{}
