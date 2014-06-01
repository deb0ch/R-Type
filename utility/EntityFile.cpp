#include <regex>

#include "EntityFile.hh"
#include "ComponentFactory.hpp"
#include "EntityFileException.hh"

//----- ----- Constructors ----- ----- //
EntityFile::EntityFile()
{}

//----- ----- Destructor ----- ----- //
EntityFile::~EntityFile()
{}

//----- ----- Operators ----- ----- //
//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
//----- ----- Methods ----- ----- //

std::pair<std::string, Entity*>		EntityFile::deserialize(std::ifstream &input) const
{
  Entity				*entity;
  std::string				key;
  ComponentFactory			cf;
  std::string				line;
  unsigned int				lineno = 1;
  bool					closed = false;
  IComponent				*component;

  cf.init();
  entity = new Entity();
  std::getline(input, line);
  line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
  if (!std::regex_match(line, std::regex("ENTITY:.+")))
    throw EntityFileException("Bad Header", lineno);
  key = line.substr(7);
  while (std::getline(input, line))
    {
      ++lineno;
      line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
      if (line[0] == '#')
	continue ;
      else if (std::regex_match(line, std::regex("COMPONENT:.+")))
	{
	  component = cf.create(line.substr(10));
	  if (!component)
	    throw EntityFileException("Component not found in factory : \""
				      + line.substr(10) + "\"", lineno);
	  component->deserializeFromFile(input, lineno);
	  entity->addComponent(component);
	}
      else if (std::regex_match(line, std::regex("!ENTITY")))
	closed = true;
      else
	throw EntityFileException("Syntax error : \"" + line + "\"", lineno);
    }
  if (!closed)
    throw EntityFileException("No closind tag", lineno);
  return (std::make_pair(key, entity));
}

void	EntityFile::serialize(const Entity *e, const std::string &key, std::ofstream &output) const
{
  if (!e)
    return ;
  output << "ENTITY:" << key << std::endl;
  std::for_each(e->_components.begin(), e->_components.end(),
		[&output] (const IComponent *c)
		{
		  output << std::string(1, '\t') << "COMPONENT:" << c->getType() << std::endl;
		  c->serializeFromFile(output, 2);
		  output << std::string(1, '\t') << "!COMPONENT" << std::endl;
		});
  output << "!ENTITY" << std::endl;
}
