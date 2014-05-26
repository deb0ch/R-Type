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

Entity		*EntityFile::deserialize(std::ifstream &input, EntityFactory &factory) {
    entity = new Entity();
    entity->deserialize(*this);
    factory.addEntity(key, entity);
}

void		EntityFile::serialize(const Entity &e)
{
  (void)e;
}
