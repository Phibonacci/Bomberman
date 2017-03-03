/**
 * @file Menus.hh
 */
#ifndef		__MENUS_HH__
# define	__MENUS_HH__

# include <Texture.hh>
# include <Geometry.hh>
# include <SdlContext.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include "ModelDraw.hh"
# include "ACamera.hh"
# include "AScreen.hh"
# include <Input.hh>
# include "Info.hpp"
# include "Peripheral.hh"
# include "GameParty.hh"
# include "Sound.hh"
# include "DirReader.hpp"
# include "Scoring.hpp"

# define	ARROW_TEXTURE		("")
# define	CREDIT_TEXTURE		("")
# define	PATH_FILE_SCORE		("")
# define	PATH_SAVEDIR		(".saves")

# define	ABS(x) ((x < 0) ? (-x) : (x))
# define	TIMEMENU	0.2f
# define	TIMEMENUCHOOSE	0.09f

class		MapEditor;


/**
 * @class Menus
 * @brief the menu
 */
class		Menus : public IScene
{
private:
  /**
   * @var _move
   * @brief the peripheral use in the menu.
   */
  Controller::Peripheral*	_move;

  /**
   * @var _info
   * @brief save the infomation for the map
   */
  Info&				_info;

  /**
   * @typedef ptrMenu
   * @brief for method function pointer used in @a update
   */
  typedef int (Menus::*ptrMenu)(gdl::Input& input, gdl::Clock const &);

  /**
   * @var _fnctMenuStack
   * @brief the stack of method function pointers use in @a update
   */
  std::stack<ptrMenu>		_fnctMenuStack;

  /**
   * @var _ptr
   * @brief method function pointer array use with @a _fnctMenuStack to do the job.
   */
  int			(Menus::*_ptr[8][8])(gdl::Input& input, gdl::Clock const &);

  /**
   * @var _editor
   * @brief the MapEditor
   */
  MapEditor*		_editor;

  /**
   * @var _val
   * @brief make coffee, choose all
   * @note use for choose what pointer have to be push in @a _fnctMenuStack
   * and @a _drawStack + to choose vector for draw bomb
   */
  int			_val;

  /**
   * @var _index
   * @brief choose what background have to be draw for menuStart.
   */
  int			_index;

  /**
   * @var _play
   * @brief the GameParty
   */
  GameParty*		_play;

  /**
   * @var _timewait
   * @var _timeaff
   * @brief use as a usleep with Clock::getElapsed
   */
  float			_timewait;
  float			_timeaff;

  /**
   * @var _sound
   * @brief the music
   */
  Zik&			_sound;

  /**
   * @var _dirread
   * @brief @a DirReader contain file for the load
   */
  DirReader		_dirread;

  /**
   * @var _tabstr
   * @brief use in @a AddVal
   */
  std::vector<std::string>	_tabstr;

  /**
   * @var _pName
   * @brief the name to save the score
   */
  std::ostringstream		_pName;

  /**
   * @typedef drawPtr
   * @brief the typedef for draw member function pointers
   */
  typedef void (Menus::*drawPtr)(Screen::AScreen &, gdl::Clock const&);

  /**
   * @var _drawStack
   * @brief the stack of draw function pointers
   */
  std::stack<drawPtr>		_drawStack;

  /**
   * @var _tabdrawptr
   * @brief the array use to choose what draw function pointer have to be push
   */
  drawPtr		_tabdrawptr[7][4];

  /**
   * @fn drawMain
   * @param scr the screen
   * @param cl the clock
   * @brief draw the main menu
   */
  void	drawMain(Screen::AScreen&scr, gdl::Clock const& cl);

  /**
   * @fn drawEditor
   * @param scr the screen
   * @param cl the clock
   * @brief draw the editor menu
   */
  void	drawEditor(Screen::AScreen&scr, gdl::Clock const& cl);

  /**
   * @fn drawPlay
   * @param scr the screen
   * @param cl the clock
   * @brief draw the play menu
   */
  void	drawPlay(Screen::AScreen&scr, gdl::Clock const& cl);

  /**
   * @fn drawMap
   * @param scr the screen
   * @param cl the clock
   * @brief draw the map menu
   */
  void	drawMap(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawPlayer
   * @param scr the screen
   * @param cl the clock
   * @brief draw the player menu
   */
  void	drawPlayer(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawMod
   * @param scr the screen
   * @param cl the clock
   * @brief draw the mod menu
   */
  void	drawMod(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawLoad
   * @param scr the screen
   * @param cl the clock
   * @brief draw the load menu
   */
  void	drawLoad(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawLoadNone
   * @param scr the screen
   * @param cl the clock
   * @brief draw the load menu when there's nothing to load
   */
  void	drawLoadNone(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawErrorMapGen
   * @param scr the screen
   * @param cl the clock
   * @brief draw the error when mapGen failled
   */
  void  drawErrorMapGen(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawCredits
   * @param scr the screen
   * @param cl the clock
   * @brief draw the credit menu
   */
  void	drawCredits(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawReplay
   * @param scr the screen
   * @param cl the clock
   * @brief draw the replay after a game with score
   */
  void	drawReplay(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawReplay
   * @param scr the screen
   * @param cl the clock
   * @brief call for hightScore
   * @note call @a drawReplay + aff player name
   */
  void	drawScorePlayer(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn drawScore
   * @param scr the screen
   * @param cl the clock
   * @brief draw the score menu
   */
  void	drawScore(Screen::AScreen& scr, gdl::Clock const& cl);

  /**
   * @fn menuStart
   * @param input the input
   * @param cl the clock
   * @return 0
   * @brief first menu where you have to press start
   */
  int	menuStart(gdl::Input& input, gdl::Clock const & cl);

  /**
   * @fn menuMain
   * @param input the input
   * @param cl the clock
   * @return 0
   * @brief the main menu
   */
  int	menuMain(gdl::Input& input, gdl::Clock const & cl);

  /**
   * @fn MenuPlay
   * @param input the input
   * @param cl the clock
   * @return 0
   * @brief the play menu
   */
  int	MenuPlay(gdl::Input& input, gdl::Clock const & cl);

  /**
   * @fn Map
   * @param input the input
   * @param cl the clock
   * @return 0
   * @brief the map menu
   */
  int	Map(gdl::Input &input, gdl::Clock const& cl);

  /**
   * @fn Player
   * @param input the input
   * @param cl the clock
   * @return 0
   * @brief the player menu
   */
  int	Player(gdl::Input &input, gdl::Clock const& cl);

  /**
   * @fn Player
   * @param input the user input
   * @return 0
   * @brief where where read the playername which's writing the user for hightscore
   */
  int	getPlayerName(gdl::Input &input);

  /**
   * @fn CheckScore
   * @param maxScore the highter score variable
   * @return 0
   * @brief get the highter score of the party
   */
  int	CheckScore(int& maxScore);

  /**
   * @fn Replay
   * @return 0
   * @brief the replay menu after a game
   */
  int	Replay(gdl::Input &input, gdl::Clock const &cl);

  /**
   * @fn MenuStart
   * @return the GameParty value, 1
   * @brief the function which start the game
   */
  int	MenuStart(gdl::Input &, gdl::Clock const &);

  /**
   * @fn MenuMod
   * @return 0
   * @brief the function where user choose the mod
   */
  int	MenuMod(gdl::Input &input, gdl::Clock const &cl);

  /**
   * @fn MenuModBomb
   * @return 0
   * @brief the function for bomb mod
   */
  int	MenuModBomb(gdl::Input &, gdl::Clock const &);

  /**
   * @fn MenuModWall
   * @return 0
   * @brief the function for Wall mod
   */
  int	MenuModWall(gdl::Input &, gdl::Clock const &);

  /**
   * @fn MenuModTP
   * @return 0
   * @brief the function for teleport mod
   */
  int	MenuModTP(gdl::Input &, gdl::Clock const &);

  /**
   * @fn MenuLoad
   * @return 0
   * @brief the menu load function
   */
  int	MenuLoad(gdl::Input &input, gdl::Clock const &cl);

  /**
   * @fn MenuEdit
   * @return 0
   * @brief the menu edit
   */
  int	MenuEdit(gdl::Input &input, gdl::Clock const &);

  /**
   * @fn MenuStartEdit
   * @return 1
   * @brief start the editor
   */
  int	MenuStartEdit(gdl::Input &, gdl::Clock const &);

  /**
   * @fn MenuOption
   * @return 0
   * @brief the menu option
   */
  int	MenuOption(gdl::Input& input, gdl::Clock const &);

  /**
   * @fn MenuCredit
   * @return 0
   * @brief the credit option
   */
  int	MenuCredit(gdl::Input& input, gdl::Clock const &);

  /**
   * @fn MenuScore
   * @return 0
   * @brief the score menu
   */
  int	MenuScore(gdl::Input& input, gdl::Clock const &);

  /**
   * @fn MenuExit
   * @return -1
   * @brief the function to exit the game
   */
  int	MenuExit(gdl::Input& input, gdl::Clock const &);

  /**
   * @fn changeVal
   * @return 0
   * @brief choose what value will be change in @a AddVal
   */
  int	changeVal(gdl::Input &input, gdl::Clock const& cl);

  /**
   * @fn AddVal
   * @param input the input
   * @param cl the clock
   * @param str the string use with @a _tabstr to choose what value is changed
   * @param min the minimum for the value
   * @param max the maximum for the value
   * @return 0
   * @brief change value in info choose with @a str and @a _tabstr.
   * @note the value will be are between @a min and @a max.
   * If @a min == @a max there is no max. longer the user press up or down,
   * faster the value is changed
   */
  int	AddVal(gdl::Input &input, gdl::Clock const &cl,
	       std::string str, size_t min, size_t max);

public:
  /**
   * @var _background
   * @brief the background picture use in menu
   */
  static std::vector<Entity*>	_background;

  /**
   * @fn MenusChoose
   * @param tabsize the max for @a val
   * @param val the value changed
   * @param move the controller checked to change val
   * @param sound the sound use to change the music
   * @brief move the @a val, the value wiich is being changed
   * @return true
   * @note +1 if user press down, -1 is the press up.
   * If @a val >= @a tabsize set @a val to 0
   */
  static bool	MenusChoose(int tabsize, int& val, Controller::Peripheral* move, Zik& sound);

  /**
   * @fn Menus
   * @param info use to set @a _info
   * @param play use to set @a _play
   * @param sound use to set @a _sound
   * @param editor use to set @a _edit
   * @brief the contructor, set menu's variables
   */
  Menus(Info& info, GameParty* play, Zik &sound, MapEditor* editor);

  /**
   * @fn ~Menus
   * @brief the destructor
   */
  virtual ~Menus();

  /**
   * @fn TranslatedSprite
   * @param gr the pictured to translated
   * @param vec the vec for the translation
   * @param cl the clock
   * @param scr the screen
   * @return true
   * @brief translate the picture in @a gr with the @a vec
   */
  static bool	TranslatedSprite(Entity* gr, glm::vec3& vec,
				 gdl::Clock const& cl, Screen::AScreen& scr);

  /**
   * @fn initScreen
   * @param scr the screen ti init
   * @brief the screen initialisation for menu
   */
  virtual void	initScreen(Screen::AScreen& scr);

  /**
   * @fn timeWaiting
   * @brief subtract to the float the getElasped of the clock
   * @return return true if float - getElasped is <= 0
   */
  static bool	timeWaiting(float&, gdl::Clock const&);

  /**
   * @fn update
   * @param cl the clock
   * @param input the input
   * @brief carry out the top of @a _fnctMenuStack.
   * @return the return of the fonction which's carry out
   */
  virtual int	update(gdl::Clock const& cl, gdl::Input &input);

  /**
   * @fn draw
   * @param screen the screen
   * @param cl the clock
   * @brief carry out the top of @a _drawStack
   * @return the return of the fonction which's carry out
   */
  virtual void	draw(Screen::AScreen &screen, gdl::Clock const& cl);

  /**
   * @fn initialize
   * @brief initialize the menu after each back into the menu
   */
  int	initialize(gdl::Input&, gdl::Clock const &);

  /**
   * @fn StartLoad
   * @brief start the loaded map
   */
  int	StartLoad(gdl::Input& input, gdl::Clock const& cl);
};

#endif		/* !__MENUS_HH__ */
