#ifndef __MAPEDITOR_HPP__
# define __MAPEDITOR_HPP__

# include <Clock.hh>
# include <Input.hh>

# include "IObject.hh"
# include "GameParty.hh"
# include "Info.hpp"
# include "Position.hh"
# include <list>

class Entity;
class Board;
class Menus;
class Player;

/**
 * @class MapEditor
 * @brief the editor class
 */
class	MapEditor : public IScene
{
  /**
   * @var _gp
   * @brief a pointer to the @a GameParty
   */
  GameParty		*_gp;

  /**
   * @var _board
   * @brief a pointer to the @a Board
   */
  Board			*_board;

  /**
   * @var _player
   * @brief the player for editor
   */
  Player*		_player;

  /**
   * @var _saveDelay
   * @brief time between to try to save
   */
  float			_saveDelay;

  /**
   * @var _playerList
   * @brief the list of created player
   */
  std::list<Player*>	_playerList;

  /**
   * @var _nai
   * @brief the ia's number
   */
  int		_nai;

  /**
   * @var _str
   * @brief the error msg if there's no player and user try to save
   */
  std::string		_str;

public:
  /**
   * @fn MapEditor
   * @param gp the @a GameParty
   * @brief the contructor
   */
  MapEditor(GameParty *gp);

  /**
   * @fn ~MapEditor
   * @brief the destructor
   */
  virtual		~MapEditor();

  /**
   * @fn initialize
   * @param info the info
   * @brief initialize the @a MapEditor
   */
  void			initialize(Info& info);

  /**
   * @fn update
   * @brief update the @a MapEditor
   */
  virtual int		update(gdl::Clock const&, gdl::Input&);

  /**
   * @fn draw
   * @brief draw the map
   */
  virtual void		draw(Screen::AScreen&, gdl::Clock const&);

  /**
   * @fn initScreen
   * @brief initialize the screen for the @a MapEditor
   */
  virtual void		initScreen(Screen::AScreen&);

  /**
   * @fn getPlayerList
   * @brief return the @a _playerList
   */
  std::list<Player*>&	getPlayerList() {return _playerList;}

  /**
   * @fn getPlayerList
   * @brief return the @a _playerList
   */
  std::list<Player*> const &	getPlayerList() const {return _playerList;}

  /**
   * @fn getNai
   * @brief return the @a _naiplayerList
   */
  int		getNai() const {return _nai;}

  /**
   * @fn getNai
   * @brief return the @a _naiplayerList
   */
  int&		getNai() {return _nai;}

  /**
   * @fn getGP
   * @brief return the @a _gp
   */
  GameParty*		getGP() const {return _gp;}
};

#endif // !__MAPEDITOR_HPP__
