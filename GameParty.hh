#ifndef GAMEPARTY_H_
# define GAMEPARTY_H_

# include "Board.hh"
# include "GamePlayer.hh"
# include "Pause.hpp"
# include "IScene.hh"
# include "Info.hpp"
# include "AScreen.hh"
# include "Thread.hh"
# include <vector>
# include "GameIA.hh"

class	Menus;
class	Pause;

/**
 * @brief the class which manage the game
 */
class	GameParty : public IScene
{
private:
  /**
   * @brief the time it write win before back to the @a Menus
   */
  static float const	victory_time;
private:
  /**
   * @brief the @a Board
   */
  Board		*_board;

  /**
   * @brief the @a GamePlayer
   */
  GamePlayer	*_player;

  /**
   * @brief the @a Pause
   */
  Pause		*_pause;

  /**
   * @brief ai manager
   */
  GameIA	*_iACenter;

  /**
   * @brief the thread
   */
  CThread::Thread	*_iAThread;

  /**
   * @brief check how many player is alive
   */
  unsigned int	_alive;

  /**
   * @brief the time to wait use as a usleep
   */
  float		_waiting;

  /**
   * @brief the time before save another time
   */
  float		_saveDelay;

  /**
   * @brief cameras player
   * @sa Screen::ACamera
   */
  std::vector<Screen::ACamera *>	_cameras;
private:

  /**
   * @param screen the screen to split
   * @brief split according to the player number
   */
  void		intelligentSplit(Screen::AScreen &screen);

  /**
   * @brief give a controller for each player
   */
  void		start();

  /**
   * @param screen the screen
   * @param clock the clock
   * @brief draw scores
   * @see Screen::AScreen
   */
  void		drawScore(Screen::AScreen &screen, gdl::Clock const &clock);
public:
  /**
   * @param pause the @a Pause
   * @brief the basic contructor
   */
  GameParty(Pause *pause);

  /**
   * @param info the map @a Info
   */
  void		initialize(Info const& info);

  /**
   * @param screen the screen
   * @brief initialize the game screen
   */
  virtual void		initScreen(Screen::AScreen &screen);

  /**
   * @see GamePlayer::getPlayer
   * @brief return the player corresponding to the index
   */
  Player	*getPlayer(unsigned int idx) const;

  /**
   * @see GamePlayer::getPlayer
   * @brief return the player corresponding to the index
   */
  Player	*&getPlayer(unsigned int idx);

  /**
   * @return @a GameParty::_player
   * @brief return @a GameParty::_player
   */
  GamePlayer	*getGamePlayer() const {return _player;}

  /**
   * @brief return the index corresponding to the player
   */
  int		getPlayerIdx(Player const *) const;

  /**
   * @return @a GameParty::_board
   * @brief return the board
   */
  Board		*&getBoard();

  /**
   * @return @a GameParty::_board
   * @brief return the board
   */
  Board		*getBoard() const {return _board;};

  /**
   * @brief set the @a GameParty::_player
   */
  void		setGamePlayer(GamePlayer *);

  /**
   * @param board the @a Board to save
   * @brief set the @a GameParty::_board
   */
  void		setBoard(Board *board);

  /**
   * @brief delete @a GameParty::_player + GameParty::_board
   */
  void		stopIA();
  void		reinit();

  /**
   * @brief save the @a GameParty
   */
  void		saveSelf(std::ostream &os);

  /**
   * @param clock the clock
   * @param input the input
   * @brief update the game
   */
  virtual int update(gdl::Clock const &clock, gdl::Input &input);

  /**
   * @brief draw the game
   */
  virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock);

  /**
   * @brief the basic destructor
   */
  virtual ~GameParty();
};

#endif /* !GAME_H_ */
