/**
 * @file Joystick.hh
 */

#ifndef BOMBJOYSTICK_HPP_
# define BOMBJOYSTICK_HPP_
#include <Input.hh>
#include "PlayerDir.hpp"
#include <SDL2/SDL_gamecontroller.h>
#include <map>

# include "IControl.hh"

namespace Controller
{
  /**
   * @class Joystick
   * @brief An interface for @class Peripheral
   */
  class Joystick : public IControl
  {
  protected:
    /**
     * @var _joy
     * @brief the GameController. There use for the joystick
     */
    SDL_GameController					*_joy;

    /**
     * @var _save
     * @brief SDL_Joystick use for exotic joystick which openGameController don't reconize
     */
    SDL_Joystick					*_save;
    /**
     * @var _tabButVal
     * @brief map translate a Controller::Button into an int
     */
    std::map<const Button, int>	_tabButVal;

    /**
     * @var _nJoyUse
     * @brief the nomber of joystick currently used
     */
    static int					_nJoyUse;

    /**
     * @var _nKeyboardUse
     * @brief the nomber of player currently using keyboard
     */
    static int					_nKeyboardUse;

  public:
    /**
     * @enum e_dir
     * @brief The enum's direction
     */
    enum e_dir
      {
	NONE,
	LEFT,
	RIGHT,
	DOWN,
	UP
      };
    /**
     * @fn Joystick
     * @brief The constructor
     */
    Joystick(const int);

    /**
     * @fn ~Joystick
     * @brief The destructor
     */
    virtual ~Joystick();

    /**
     * @fn getJoy
     * @brief return the SDL_Joystick in the variable @var _joy
     * @return the SDL_Joystick in @var _joy
     */
    SDL_Joystick* getJoy() const;

    /**
     * @fn getControl
     * @brief return  _joy the SDL_GameController to the current joystick
     * @return _joy the SDL_GameController
     */
    SDL_GameController* getControl();

    /**
     * @fn getValToBut
     * @brief return tu tranlation for but in @var _tabButVal
     * @param but the value of the map translation
     * @return the translation of @var _tabButVal
     */
    int	getValToBut(Button but) const;

    /**
     * @fn setValToBut
     * @brief set the value in the map
     * @param but the value for translate
     * @param val the value to modify
     */
    void		setValToBut(Button const but, int const val);

    virtual void	checkMove(gdl::Input& input) = 0;
    virtual PlayerDir const&	getDir() const = 0;
    virtual Button	getBut() = 0;
  };
};

#endif // !BOMBJOYSTICK_HPP_
