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
  : AComponent("EntitySpawnerComponent"),
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
}

EntitySpawnerComponent::EntitySpawnerComponent(const EntitySpawnerComponent &ref)
  : AComponent("EntitySpawnerComponent")
{
  _entities = ref._entities;
  _components = ref._components;
  _nb = ref._nb;
  _delay = ref._delay;
  _min_pos = ref._min_pos;
  _max_pos = ref._max_pos;
  _random = ref._random;
  _abs = ref._abs;
  _next = ref._next;
  _active = ref._active;
}

//----- ----- Destructor ----- ----- //
EntitySpawnerComponent::~EntitySpawnerComponent()
{}

//----- ----- Operators ----- ----- //
EntitySpawnerComponent	&EntitySpawnerComponent::operator=(const EntitySpawnerComponent &ref)
{
  _entities = ref._entities;
  _components = ref._components;
  _nb = ref._nb;
  _delay = ref._delay;
  _min_pos = ref._min_pos;
  _max_pos = ref._max_pos;
  _random = ref._random;
  _abs = ref._abs;
  _next = ref._next;
  _active = ref._active;
  return (*this);
}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
void			EntitySpawnerComponent::setActive(bool active)
{
  this->_active = active;
}
//----- ----- Methods ----- ----- //
Entity			*EntitySpawnerComponent::spawnEntity(EntityFactory *facto, const Pos2DComponent *pos)
{
  static unsigned long	counter = 0;
  static unsigned long	tick = 0;
  Entity		*res = NULL;
  Pos2DComponent	*res_pos = NULL;

  if (!this->_active)
    return (NULL);

  if ((tick++ < this->_delay) ||
      (this->_nb > 0 && counter >= _nb) ||
      this->_entities.size() == 0)
    return (NULL);

  if (tick >= this->_delay)
    tick = 0;

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

  res_pos = res->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!res_pos)
    res->addComponent((res_pos = new Pos2DComponent(0, 0)));
  if (!this->_abs && pos)
    {
      res_pos->setX(pos->getX());
      res_pos->setY(pos->getY());
    }
  res_pos->setX(pos->getX() + RandomReal()(this->_min_pos.first, this->_max_pos.first));
  res_pos->setY(pos->getY() + RandomReal()(this->_min_pos.second, this->_max_pos.second));

  ++counter;
  return (res);
}
