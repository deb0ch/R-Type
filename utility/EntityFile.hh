#ifndef ENTITYFILE_H_
# define ENTITYFILE_H_

# include	<fstream>

class EntityFile
{
public:
  EntityFile();
  ~EntityFile();

  Entity	*deserialize(std::ifstream &input, EntityFactory &factory);
  std::ofstream	serialize(const Entity &);
};

#endif /* !ENTITYFILE_H_ */
