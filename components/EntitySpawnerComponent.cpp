#include	<numeric>
#include	"EntitySpawnerComponent.hh"

#include	"EntityFactory.hpp"
#include	"ComponentFactory.hpp"
#include	"RandomInt.hpp"
#include	"RandomReal.hpp"

//----- ----- Constructors ----- ----- //
EntitySpawnerComponent::EntitySpawnerComponent(std::vector<std::pair<std::string, unsigned int>> entities,
					       std::vector<IComponent*> components,
					       unsigned long nb,
					       float delay,
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

  this->_maxWeight = 0;
  std::for_each(this->_entities.begin(),
		this->_entities.end(),
		[this] (std::pair<std::string, unsigned int> &p) {
		  if (p.second <= 0)
		    p.second = 1;
		  this->_maxWeight += p.second;
		});
}

EntitySpawnerComponent::EntitySpawnerComponent(const EntitySpawnerComponent& ref)
  : ACopyableComponent("EntitySpawnerComponent"),
    _entities(ref._entities),
    _maxWeight(ref._maxWeight),
    _nb(ref._nb),
    _delay(ref._delay),
    _min_pos(ref._min_pos),
    _max_pos(ref._max_pos),
    _random(ref._random),
    _abs(ref._abs)
{
  this->_next = 0;
  this->_active = true;
  this->_counter = 0;
  this->_tick = 0;

  std::for_each(ref.getComponents().begin(),
		ref.getComponents().end(),
		[this] (IComponent* comp) -> void {
		  this->_components.push_back(comp->clone());
		});
}

//----- ----- Destructor ----- ----- //
EntitySpawnerComponent::~EntitySpawnerComponent()
{
  std::for_each(this->getComponents().begin(),
		this->getComponents().end(),
		[] (IComponent* comp) -> void {
		  delete comp;
		});
}

//----- ----- Operators ----- ----- //
//----- ----- Getters ----- ----- //
bool				EntitySpawnerComponent::isAbsolute() const
{
  return (this->_abs);
}

const std::pair<float, float>	EntitySpawnerComponent::getCoordinates() const
{
  return (std::make_pair(RandomReal()(this->_min_pos.first, this->_max_pos.first),
			 RandomReal()(this->_min_pos.second, this->_max_pos.second)
			 )
	  );
}

const std::vector<IComponent*>	&EntitySpawnerComponent::getComponents() const
{
  return (this->_components);
}

//----- ----- Setters ----- ----- //
void			EntitySpawnerComponent::setActive(bool active)
{
  this->_active = active;
}

void			EntitySpawnerComponent::clearEntities()
{
	this->_entities.clear();
}

void			EntitySpawnerComponent::addEntity(const std::pair<std::string, unsigned int> &value)
{
	this->_entities.push_back(value);
}

//----- ----- Methods ----- ----- //
Entity			*EntitySpawnerComponent::spawnEntity(EntityFactory *facto, float delta)
{
  Entity		*res = NULL;

  if (this->_tick < this->_delay)
    {
      this->_tick += delta;
      return (NULL);
    }
  // return ((Entity *) (0 * ++this->_tick)); // wtf seriously?

  if (!this->_active ||
      (this->_nb > 0 && this->_counter >= _nb) ||
      this->_entities.size() == 0)
    return (NULL);

  this->_tick -= this->_delay;

  if (facto)
    res = facto->create(this->_entities[this->_next].first);
  if (!this->_random)
    {
      ++this->_next;
      if (this->_next >= this->_entities.size())
	this->_next = 0;
    }
  else
    {
      unsigned int	r;
      unsigned int	cumul = 0;

      r = RandomInt().operator() <unsigned long>(1, this->_maxWeight);

      for (unsigned int i = 0 ; i < this->_entities.size() ; ++i)
	{
	  if (r <= this->_entities[i].second + cumul)
	    {
	      this->_next = i;
	      break ;
	    }
	  cumul += this->_entities[i].second;
	}
    }

  if (!res)
    return (NULL);

  ++this->_counter;
  return (res);
}

void			EntitySpawnerComponent::serialize(IBuffer &) const
{}

void			EntitySpawnerComponent::unserialize(IBuffer &)
{}

void	EntitySpawnerComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  ComponentFactory	cf;
  cf.init();

  if (std::regex_match(lastline, std::regex("entity=.+")))
    this->_entities.push_back(std::make_pair(lastline.substr(7, lastline.find(';') - 7), std::stoul(lastline.substr(lastline.find(';') + 1))));
  else if (std::regex_match(lastline, std::regex("nb=.+")))
    this->_nb = std::stoul(lastline.substr(3));
  else if (std::regex_match(lastline, std::regex("delay=.+")))
    this->_delay = std::stof(lastline.substr(6));
  else if (std::regex_match(lastline, std::regex("minPosX=.+")))
    this->_nb = std::stof(lastline.substr(8));
  else if (std::regex_match(lastline, std::regex("minPosY=.+")))
    this->_nb = std::stof(lastline.substr(8));
  else if (std::regex_match(lastline, std::regex("maxPosX=.+")))
    this->_nb = std::stof(lastline.substr(8));
  else if (std::regex_match(lastline, std::regex("maxPosY=.+")))
    this->_nb = std::stof(lastline.substr(8));
  else if (std::regex_match(lastline, std::regex("random=.+")))
    this->_nb = (lastline.substr(7) == "true");
  else if (std::regex_match(lastline, std::regex("abs=.+")))
    this->_nb = (lastline.substr(4) == "true");
  else if (std::regex_match(lastline, std::regex("component=COMPONENT:.+")))
    {
      IComponent	*compo;

      compo = cf.create(lastline.substr(20));
      if (!compo)
	throw EntityFileException("Component doesn't exist in Factory : \"" + lastline.substr(20) + "\"", lineno);
      compo->deserializeFromFile(input, lineno);
      this->_components.push_back(compo);
    }
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void			EntitySpawnerComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  std::for_each(this->_entities.begin(), this->_entities.end(), [&output, indent](const std::pair<std::string, int> &p)
		{
		  output << std::string(indent, '\t') << "entity=" << p.first << ";" << p.second << std::endl;
		});
  std::for_each(this->_components.begin(), this->_components.end(), [&output, indent](const IComponent *c)
		{
		  output << std::string(indent, '\t') << "component=COMPONENT:" << c->getType() << std::endl;
		  c->serializeFromFile(output, indent + 1);
		  output << std::string(indent, '\t') << "!COMPONENT" << std::endl;
		});
  output << std::string(indent, '\t') << "nb=" << this->_nb << std::endl;
  output << std::string(indent, '\t') << "delay=" << this->_delay << std::endl;
  output << std::string(indent, '\t') << "minPosX=" << this->_min_pos.first << std::endl;
  output << std::string(indent, '\t') << "minPosY=" << this->_min_pos.second << std::endl;
  output << std::string(indent, '\t') << "maxPosX=" << this->_max_pos.first << std::endl;
  output << std::string(indent, '\t') << "maxPosY=" << this->_max_pos.second << std::endl;
  output << std::string(indent, '\t') << "random=" << std::boolalpha << this->_random << std::endl;
  output << std::string(indent, '\t') << "abs=" << std::boolalpha << this->_abs << std::endl;
}
