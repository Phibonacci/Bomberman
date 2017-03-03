/**
 * @file PlayerDir.hpp
 */

#ifndef __PLAYERDIR_HPP__
# define __PLAYERDIR_HPP__

/**
 * @brief the max for joysticks' axis
 */
# define RAYON 32767.0f

/**
 * @class PlayerDir
 * @brief the class which contain the angle and the speed to move the player
 */
class PlayerDir
{
  /**
   * @var _angle
   * @brief the angle in degree using the trigonomitry
   * @note
   *            90
   *             |
   *             |
   *  180,-180------- 0
   *             |
   *             |
   *            -90
   */
  float		_angle;

  /**
   * @var _speed
   * @brief the speed which the player move
   */
  float		_speed;

public:
  /**
   * @fn PlayerDir
   * @brief the contructor, initialize values
   */
  PlayerDir();

  /**
   * @fn ~PlayerDir
   * @brief the desctuctor
   */
  ~PlayerDir();

  /**
   * @fn xyToAngle
   * @param x the x
   * @param y the y
   * @brief use x and y to st the angle using trigonometry
   */
  void		xyToAngle(int x, int y);

  /**
   * @fn setAngle
   * @param angle the angle use to set
   * @brief set the @a _angle with @a angle
   */
  void		setAngle(float const& angle);

  /**
   * @param speed the speed use to set
   * @brief set @a _speed with @a speed
   */
  void		setSpeed(int speed);

  /**
   * @param speed the speed use to set
   * @brief set @a _speed with @a speed
   */
  void		setSpeed(float speed);

  /**
   * @fn getAngle
   * @return @a _angle the angle
   * @brief return the angle
   */
  float const&	getAngle() const;

  /**
   * @fn getSpeed
   * @return @a _speed the speed
   * @brief return the speed
   */
  float	const&	getSpeed() const;
};

#endif // !__PLAYERDIR_HPP__
