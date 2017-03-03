#ifndef __INFO_HPP__
# define __INFO_HPP__

#include <iostream>

/**
 * @class Info
 * @brief contain the map informations
 */
class Info
{
  /**
   * @brief the players number
   */
  size_t	_nplayers;

  /**
   * @brief the ais bumber
   */
  size_t	_nai;

  /**
   * @brief the map x
   */
  size_t	_mapX;

  /**
   * @brief the map y
   */
  size_t	_mapY;

  /**
   * @brief the free block ratio
   */
  size_t	_free;

  /**
   * @brief the undestructible block ratio
   */
  size_t	_unde;

  /**
   * @brief the real free ratio
   */
  size_t	_realFree;

  /**
   * @brief the real undestructible block ratio
   */
  size_t	_realUnde;

public:
  /**
   * @brief the mods
   */
  typedef enum		Mod
    {
      NONE,
      MOVEBOMB,
      TELEPORT,
      WALL
    }			Mod;
private:
  /**
   * @brief the mod choose
   */
  Mod	_mod;

  /**
   * @brief the load file path
   */
  std::string	_savefile;

  /**
   * @brief if the maze if perfect or not
   */
  size_t	_perfectMaze;
public:

  /**
   * @brief the contructor
   */
  Info();

  /**
   * @brief the desctructor
   */
  ~Info();

  /**
   * @return @a _nplayer
   * @brief return the number of player
   */
  size_t	&getNPlayers() {return _nplayers;}

  /**
   * @return @a _nai
   * @brief return the number of ai
   */
  size_t	&getNAi() {return _nai;}

  /**
   * @return @a _mapX
   * @brief return the x size
   */
  size_t	&getMapX() {return _mapX;}

  /**
   * @return @a _mapY
   * @brief return the y size
   */
  size_t	&getMapY() {return _mapY;}

  /**
   * @return @a _free
   * @brief return the free ratio
   */
  size_t	&getFreeBlock() {return _free;}

  /**
   * @return @a _unde
   * @brief return the unde ratio
   */
  size_t	&getUndeBlock() {return _unde;}

  /**
   * @return @a _realFree
   * @brief return the real free ratio
   */
  size_t	&getRealFree() {return _realFree;}

  /**
   * @return @a _realUnde
   * @brief return the real unde ratio
   */
  size_t	&getRealUnde() {return _realUnde;}

  /**
   * @return @a _perfectMaze
   * @brief return the perfect Maze value
   */
  size_t	&getPerfectMaze() {return _perfectMaze;}

  /**
   * @return @a _nplayer
   * @brief return the number of player
   */
  size_t	getNPlayers() const {return _nplayers;}

  /**
   * @return @a _nai
   * @brief return the number of ai
   */
  size_t	getNAi() const {return _nai;}

  /**
   * @return @a _mapX
   * @brief return the x size
   */
  size_t	getMapX() const {return _mapX;}

  /**
   * @return @a _mapY
   * @brief return the y size
   */
  size_t	getMapY() const {return _mapY;}

  /**
   * @return @a _free
   * @brief return the free ratio
   */
  size_t	getFreeBlock() const {return _free;}

  /**
   * @return @a _unde
   * @brief return the unde ratio
   */
  size_t	getUndeBlock() const {return _unde;}

  /**
   * @return @a _realFree
   * @brief return the real free ratio
   */
  size_t	getRealFree() const {return _realFree;}

  /**
   * @return @a _realUnde
   * @brief return the real unde ratio
   */
  size_t	getRealUnde() const {return _realUnde;}

  /**
   * @return @a _perfectMaze
   * @brief return the perfect Maze value
   */
  size_t	getPerfectMaze() const {return _perfectMaze;}

  /**
   * @return @a _mod
   * @brief return the mod choosen
   */
  Mod		&getMod() {return _mod;}

  /**
   * @return @a _mod
   * @brief return the mod choosen
   */
  Mod		getMod() const {return _mod;}

  /**
   * @return @a _savefile
   * @brief return the load file path
   */
  std::string&		getSaveFile() {return _savefile;}

  /**
   * @return @a _savefile
   * @brief return the load file path
   */
  std::string const&	getSaveFile() const {return _savefile;}
};

#endif // !__INFO_HPP__
