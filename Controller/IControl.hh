/**
 * @file IControl.hh
 */

#ifndef ICONTROL_HH_
# define ICONTROL_HH_

# include "PlayerDir.hpp"

/**
 * @brief controllers namespace
 */
namespace	Controller
{
  /**
   * @enum Button
   * @brief the Button for the check in the controller
   */
  enum Button
    {
      BUTTON_INVALID = -1,
      BUTTON_PUTBOMB,
      BUTTON_MODE,
      BUTTON_X,
      BUTTON_Y,
      BUTTON_BACK,
      BUTTON_GUIDE,
      BUTTON_START,
      BUTTON_LEFTSTICK,
      BUTTON_RIGHTSTICK,
      BUTTON_LEFTSHOULDER,
      BUTTON_RIGHTSHOULDER,
      BUTTON_DPAD_UP,
      BUTTON_DPAD_DOWN,
      BUTTON_DPAD_LEFT,
      BUTTON_DPAD_RIGHT,
      BUTTON_MAX
    };

  /**
   * @class IControl
   * @brief The controller interface
   */
  class IControl
  {
  protected:

  public:

    /**
     * @fn checkMove
     * @brief check and return player's move
     * @return players array move
     */
    virtual void	checkMove(gdl::Input& input) = 0;

    /**
     * @fn getDir
     * @brief Return @a _dir value
     * @return A @a _dir copy value
     */
    virtual PlayerDir const& getDir() const = 0;

    /**
     * @fn getBut
     * @brief Return Controller::Button value
     * @return A @a _but copy value
     */
    virtual Button	getBut() = 0;

  public:
    /**
     * @fn ~IControl
     * @brief the destructor
     */
    virtual	~IControl() {}
  };
};
#endif // !ICONTROL_HH_
