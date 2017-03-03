#ifndef __PAUSE_HPP__
# define __PAUSE_HPP__

# include "IObject.hh"
# include "AScreen.hh"
# include "IControl.hh"
# include <Clock.hh>
# include <Input.hh>
# include <stack>
# include "IScene.hh"
# include "Sound.hh"
# include <AShader.hh>

class GameParty;
class Entity;

/**
 * @class Pause
 * @brief the pause class
 */
class Pause : public IScene
{
  /**
   * @typedef pausePtr
   * @brief the pointer on method pointer function
   */
  typedef int	(Pause::*pausePtr)(gdl::Clock const&, gdl::Input&);

  /**
   * @var _pausePtr
   * @brief pause pointer stack to say where we are un pause.
   */
  std::stack<pausePtr>			_pausePtr;

  /**
   * @var _val
   * @brief use for choose what to push or aff
   */
  int					_val;

  /**
   * @var _move
   * @brief the controller to move in the pause
   */
  Controller::IControl			*_move;

  /**
   * @var _timewait
   * @brief it's like a usleep with getElasped
   */
  float					_timewait;

  /**
   * @var _ptrfnct
   * @brief the function pointer array
   */
  pausePtr				_ptrfnct[3][6];

  /**
   * @var _gp
   * @brief the gameParty
   */
  GameParty*				_gp;

  /**
   * @var _idx
   * @brief the index
   */
  unsigned int				_idx;

  /**
   * @var _sound
   * @brief the music
   */
  Zik&					_sound;

  /**
   * @var _drawfnct
   * @brief the pointer to draw
   */
  void				(Pause::*_drawfnct)(Screen::AScreen&, gdl::Clock const&);

  /**
   * @fn returnToGame
   * @brief the function to return to game
   */
  int		returnToGame(gdl::Clock const&, gdl::Input&);

  /**
   * @fn backToMenu
   * @brief the function to back to menu
   */
  int		backToMenu(gdl::Clock const&, gdl::Input&);

  /**
   * @fn WaitInPause
   * @brief the pause to wait
   */
  int		WaitInPause(gdl::Clock const&, gdl::Input&);

  /**
   * @fn drawPause
   * @param sc the screen
   * @param cl the clock
   * @brief the function to draw pause menu
   */
  void		drawPause(Screen::AScreen& sc, gdl::Clock const&cl);

  /**
   * @fn drawCommand
   * @param sc the screen
   * @param cl the clock
   * @brief draw the command pause menu
   */
  void		drawCommand(Screen::AScreen& sc, gdl::Clock const&cl);

  /**
   * @fn TranslatedSprite
   * @param gr the ground to translated
   * @param vec the vector use for translation
   * @param cl the clock
   * @param scr the screen
   * @param shader the shader
   * @return true
   * @brief translate @a gr with @a vec
   */
  bool	TranslatedSprite(Entity* gr, glm::vec3 const& vec,
			 gdl::Clock const& cl, Screen::ASubScreen& scr,
			 gdl::AShader& shader);

  /**
   * @fn Commands
   * @return 2
   * @brief the command to change button
   */
  int			Commands(gdl::Clock const&, gdl::Input&);

  /**
   * @fn CommandsBomb
   * @param cl the clock
   * @param input the input
   * @return 2
   * @brief the function to change the putbomb button
   */
  int			CommandsBomb(gdl::Clock const& cl, gdl::Input& input);

  /**
   * @fn CommandsMode
   * @return 2
   * @brief the function to change the mode button
   */
  int			CommandsMode(gdl::Clock const&, gdl::Input&);

  /**
   * @fn CommandsStart
   * @return 2
   * @brief the function to change the start button
   */
  int			CommandsStart(gdl::Clock const&, gdl::Input&);

  /**
   * @fn CommandsUpCam
   * @return 2
   * @brief the function to change the upcam button
   */
  int			CommandsUpCam(gdl::Clock const&, gdl::Input&);

  /**
   * @fn CommandsDownCam
   * @return 2
   * @brief the function to change the downcam button
   */
  int			CommandsDownCam(gdl::Clock const&, gdl::Input&);

public:
  /**
   * @fn Pause
   * @brief the contructor
   */
  Pause(Zik&);

  /**
   * @fn ~Pause
   * @brief the destructor
   */
  virtual ~Pause();

  /**
   * @fn initialize
   * @param move the controller
   * @param gp the gameparty
   * @param idx the index
   * @brief initialize the pause
   */
  void		initialize(Controller::IControl* move, GameParty *gp,
			   unsigned int idx);

  /**
   * @fn update
   * @brief update the pause
   */
  virtual int	update(gdl::Clock const&, gdl::Input&);

  /**
   * @fn draw
   * @brief draw the pause
   */
  virtual void	draw(Screen::AScreen&, gdl::Clock const&);

  /**
   * @fn initScreen
   * @brief init the screen for the pause
   */
  virtual void	initScreen(Screen::AScreen&);
};


#endif // !__PAUSE_HPP__
