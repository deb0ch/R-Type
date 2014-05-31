#ifndef ENTITYFILE_H_
# define ENTITYFILE_H_

# include	<fstream>
# include	<utility>

# include	"Entity.hh"

class EntityFile
{
public:
  EntityFile();
  ~EntityFile();

  std::pair<std::string, Entity*>	deserialize(std::ifstream &input);
  void					serialize(const Entity *e, const std::string &key, std::ofstream &output);
};

#endif /* !ENTITYFILE_H_ */
