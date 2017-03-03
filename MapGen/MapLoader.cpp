#include <iostream>
#include "MapLoader.hh"
#include "Case.hh"
#include "Content.hh"
#include "EntityFactory.hh"
#include "Entity.hpp"
#include <glm/glm.hpp>

MapLoader::t_gen const MapLoader::generations[8] =
  {
    &MapLoader::genUndestructible,
    &MapLoader::genBlock,
    &MapLoader::genPlayer,
    NULL,
    NULL,
    NULL,
    &MapLoader::genTP,
    &MapLoader::genUndestructible
  };

MapLoader::MapLoader(GameParty const &g, const Info &info)
  : _g(g), _info(info), _playeridx(0)
{
}

void		MapLoader::genUndestructible(Board *rt, int rx, int ry)
{
  Entity	*entity;

  entity = EntityFactory::NewUndestructibleBlock(rt, glm::vec3(rx, 0, ry), _info.getMod());
  rt->addEntity(entity);
}

void		MapLoader::genPlayer(Board *rt, int rx, int ry)
{
  Entity	*entity;

  entity = EntityFactory::NewPlayer(rt, glm::vec3(rx, 0, ry),
				    _g.getPlayer(_playeridx));
  rt->addEntity(entity);
  _playeridx++;
}

void		MapLoader::genBlock(Board *rt, int rx, int ry)
{
  Entity	*entity;

  entity = EntityFactory::NewBlock(rt, glm::vec3(rx, 0, ry), _info.getMod());
  rt->addEntity(entity);
}

void		MapLoader::genTP(Board *rt, int rx, int ry)
{
  Entity	*entity;

  entity = EntityFactory::NewTeleportBlock(rt, glm::vec3(rx, 0, ry), _info.getMod());
  rt->addEntity(entity);
}

Board		*MapLoader::loadMap()
{
  int	rx(_info.getMapX() / 2);
  int	ry(_info.getMapY() / 2);
  Content	algomap(ry, rx);
  std::vector<std::vector<Types> > map((ry * 2 + 1),
				       std::vector<Types>((rx * 2 + 1), Types()));
  Board		*rt;
  int	x, y;

  x = ry / 2;
  y = rx / 2;
  while (!algomap.core(x, y))
    ;
  x = ry / 2;
  y = rx / 2;
  algomap.Convert(map, _info.getPerfectMaze());
  algomap.putPlayer(_info.getNPlayers() + _info.getNAi(), map, x * y * 100);
  algomap.Finalyze(map, _info.getRealFree(), _info.getRealUnde());
  x = rx * 2 + 1;
  y = ry * 2 + 1;
  rt = new Board(rx * 2 + 1, ry * 2 + 1);
  ry = 0;
  while (ry < y)
    {
      rx = 0;
      while (rx < x)
	{
	  int		t = map[ry][rx];
	  t_gen		ptr;

	  if (t > 0 && (t - 1) < static_cast<int>(sizeof(generations) / sizeof(*generations))
	      && map[ry][rx] == t && (ptr = generations[t - 1]))
	    (this->*ptr)(rt, rx, ry);
	  ++rx;
	}
      ++ry;
    }
  return (rt);
}
