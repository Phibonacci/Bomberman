/**
 * @file Peripheral.hh
 */

#ifndef INTERACTION_HPP
# define INTERACTION_HPP

# include <Input.hh>
# include "SdlContext.hh"
# include "Joystick.hh"
# include "IControl.hh"

namespace Controller
{
  /**
   * @class Peripheral
   * @brief Contain de direction where the player have to go
   * @note One Interation class per player not more than 4 player are accepted:
   * 4 with Joystick max and 2 with keyboard max
   */
  class Peripheral : public Joystick
  {
  public:

  private:
    /**
     * @var _but
     * @brief the button pressed
     * @note	SDL_CONTROLLER_BUTTON_INVALID = -1,
     *		SDL_CONTROLLER_BUTTON_A,
     *		SDL_CONTROLLER_BUTTON_B,
     *		SDL_CONTROLLER_BUTTON_X,
     *		SDL_CONTROLLER_BUTTON_Y,
     *		SDL_CONTROLLER_BUTTON_BACK,
     *		SDL_CONTROLLER_BUTTON_GUIDE,
     *		SDL_CONTROLLER_BUTTON_START,
     *		SDL_CONTROLLER_BUTTON_LEFTSTICK,
     *		SDL_CONTROLLER_BUTTON_RIGHTSTICK,
     *		SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
     *		SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
     *		SDL_CONTROLLER_BUTTON_DPAD_UP,
     *		SDL_CONTROLLER_BUTTON_DPAD_DOWN,
     *		SDL_CONTROLLER_BUTTON_DPAD_LEFT,
     *		SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
     *		SDL_CONTROLLER_BUTTON_MAX
     */
    Button	_but;

    /**
     * @var _dir
     * @brief the direction
     */
    PlayerDir _dir;

    /**
     * @var _playerkeys
     * @brief the keys saved for the player
     */
    std::map<int, int>		_playerkeys;

    /**
     * @var _sensi
     * @brief the sensibility for joysticks
     */
    size_t	_sensi;

  public:
    /**
     * @brief The constructor
     * @param nbJoy the number of connected joystick to the computer
     * @param sensi the sensibility of the joystick
     */
    Peripheral(int nbJoy, size_t sensi);

    /**
     * @brief The destructor
     */
    virtual ~Peripheral();

  private:
    /**
     * @fn setDir
     * @brief Set @a _dir with the value
     */
    void	setDir(enum e_dir);

    /**
     * @fn setBut
     * @param but the value to set to _but
     * @brief Set @a _but with the value
     */
    void		setBut(Controller::Button but);

    /**
     * @brief check is hat are pressing for each player
     */
    void	checkHat();

    /**
     * @brief check if axes are in use for each player
     * @return True if an axes is use else false
     */
    bool	checkAxes();

    /**
     * @brief check if buttons are pressing for each player
     * @return The button pressed or -1 if nothing is pressed
     */
    int		checkButtons();

    /**
     * @brief check which button is pressed at the moment by the joystick
     * @return The button pressed or -1 if nothing is pressed
     */
    int		checkJoyButton();

    /**
     * @brief change value between two buttons
     */
    void	changeBut();

    /**
     * @brief Check if some keys are pressed
     * @param input The input
     */
    bool	checkKeys(gdl::Input& input);

    /**
     * @brief display what keys are saved for the player
     */
    void	displaySaveKeys();

    /**
     * @brief save keys for the player
     */
    void	saveKeys();

    /**
     * @brief set the sensibility
     * @param sensi the sensibility to set
     */
    void	setSensi(size_t sensi);

    /**
     * @brief return the sensibility of the joystick
     * @return the sensibility
     */
    size_t getSensi() const;

    /**
     * @brief return the boolean use for ckeck if the player use a joystick or not
     * @return return @a _useJoy
     */
    bool	getUseJoy() const;

  public:

    /**
     * @fn checkMove
     * @brief check and return player's move
     * @return players array move
     */
    virtual void	checkMove(gdl::Input& input);

    /**
     * @fn getDir
     * @brief Return @a _dir value
     * @return A @a _dir copy value
     */
    virtual PlayerDir const&	getDir() const;

    /**
     * @fn getBut
     * @brief Return @a _but value
     * @return A @a _but copy value
     */
    virtual Button	getBut();

    /**
     * @brief Check what button is pressed and return the value
     * @return A copy of the value button pressed value
     */
    Button	retJoyBut();
    Button	retJoyButton();
  };
};

#endif // !INTERACTION_HPP
