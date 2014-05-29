#ifndef QUADTREE_H_
# define QUADTREE_H_

# include <vector>
# include "Pos2DComponent.hh"
# include "Box2DComponent.hh"
# include "Entity.hh"

class	QuadTree
{

protected:

  World			*_world;
  unsigned int		maxEntities;
  QuadTree		*NorthWestBlock;
  QuadTree		*NorthEastBlock;
  QuadTree		*SouthWestBlock;
  QuadTree		*SouthEastBlock;
  std::vector<Entity *>	Entities;
  float			_x, _y, _width, _height;

public:

  QuadTree(World *, std::vector<Entity *> const &, float, float, float, float, int);
  ~QuadTree();

  std::vector<Entity *> const &getEntities() const;
  bool	isInBlock(Pos2DComponent *, Box2DComponent *);
  std::vector<Entity *> const &findTree(Entity *);
  void	DrawDebug();
};

#endif /* !QUADTREE_H_ */
