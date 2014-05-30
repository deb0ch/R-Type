#include	"EntityFile.hh"

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

std::pair<std::string, Entity*>		EntityFile::deserialize(std::ifstream &input, const ComponentFactory &cf) {
  Entity	*entity;
  std::string	key;

  entity = new Entity();
  //entity->deserializeFromFile(input, cf);
  (void)input;
  (void)cf;
  return (std::make_pair(key, entity));
}

void					EntityFile::serialize(const Entity *e, const std::string &key, std::ofstream &output)
{
  if (!e)
    return ;
  output << "ENTITY:" << key << std::endl;
  std::for_each(e->_components.begin(), e->_components.end(), [&output](const IComponent *c)
		{
		  output << std::string(1, '\t') << "COMPONENT:" << c->getType() << std::endl;
		  c->serializeFromFile(output, 2);
		  output << std::string(1, '\t') << "!COMPONENT" << std::endl;
		});
  output << "!ENTITY" << std::endl;
}
