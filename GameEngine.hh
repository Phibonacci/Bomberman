#ifndef GAMEENGINE_H_
# define GAMEENGINE_H_

#include <Game.hh>
#include <SdlContext.hh>
#include <vector>
#include <Model.hh>
#include "Board.hh"
#include "AScreen.hh"
#include <SDL2/SDL.h>
#include "Info.hpp"
#include "Menus.hh"
#include "Sound.hh"

/**
 * @brief the game controller
 */
class GameEngine : public gdl::Game
{
private:
  /**
   * @brief copy the contructor for copelian form
   */
  GameEngine(GameEngine const &);

  /**
   * @brief copy operator copelian form
   */
  GameEngine & operator=(GameEngine const &);
public:

  /**
   * @brief the contructor
   */
  GameEngine();

  /**
   * @brief the destructor
   */
  virtual ~GameEngine();

private:
  /**
   * @brief the context for input and clock
   */
  gdl::SdlContext	_context;

  /**
   * @brief the screen
   */
  Screen::AScreen	_screen;

  /**
   * @brief the clock
   */
  gdl::Clock		_clock;

  /**
   * @brief the input actualizer
   */
  gdl::Input		_input;

  /**
   * @brief the map information
   */
  Info			_info;

  /**
   * @brief the scene array, contain @a Menus @a Pause @a GameParty @a MapEditor
   */
  IScene		*_scenes[5];

  /**
   * @brief the current scene
   */
  int			_current;

  /**
   * @brief change the current
   */
  void			changeCurrent(int current);
public:
  /**
   * @brief the sound
   */
  static Zik		_sound;

  /**
   * @brief initialize the gameEngine variables
   */
  virtual bool initialize();

  /**
   * @brief update the current scene
   */
  virtual bool update();

  /**
   * @brief draw the current scene
   */
  virtual void draw();
};

#endif /* !GAMEENGINE_H_ */
