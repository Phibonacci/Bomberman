#ifndef MAPLOADER_H_
# define MAPLOADER_H_

# include "GameParty.hh"
# include "Board.hh"
# include "Info.hpp"

/**
 ** @brief This class is a coding factory for the Map
 */
class	MapLoader
{
private:
  typedef void (MapLoader::*t_gen)(Board *, int, int);
  static t_gen const	generations[8];
  GameParty const &_g;
  Info const	&_info;
  int		_playeridx;

public:
  /**
   ** Class constructor works with a gameparty and info
   ** @param g
   ** @param info
   */
  MapLoader(GameParty const &g, const Info &info);

  /**
   ** This function returns a Board of the actual map
   */
  Board	*loadMap();

  /**
   ** This functions generates a player on the board on the given coordinates
   ** @param rt
   ** @param rx
   ** @param ry
   */
  void genPlayer(Board *rt, int rx, int ry);

  /**
   ** This functions generates an undestructible block on the board on the given coordinates
   ** @param rt
   ** @param rx
   ** @param ry
   */
  void genUndestructible(Board *rt, int rx, int ry);

  /**
   ** This functions generates a destructible block on the board on the given coordinates
   ** @param rt
   ** @param rx
   ** @param ry
   */
  void genBlock(Board *rt, int rx, int ry);

  /**
   ** This functions generates a TP on the board on the given coordinates
   ** @param rt
   ** @param rx
   ** @param ry
   */
  void genTP(Board *rt, int rx, int ry);
};

#endif /* !MAPLOADER_H_ */

