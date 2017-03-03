/**
 * @file RotateDraw.hh
 */
#ifndef ROTATE_DRAW_H_
# define ROTATE_DRAW_H_

# include "ModelDraw.hh"

/**
 * @class RotateDraw
 * @brief draw and object in rotation (ex : bonus)
 */
class RotateDraw : public GeometryDraw
{
  /**
   * @var _angle
   * @brief angle of the rotation
   */
  float		_angle;
public:
  /**
   * @brief constructor
   */
  RotateDraw(std::string const& str);
  /**
   * @brief constructor
   */
  RotateDraw(std::istream & is);
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream &os) const;
  /**
   * @fn draw
   * @brief draw the element
   */
  virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock);
  /**
   * @fn ~RotateDraw
   * @brief destructor
   */
  virtual ~RotateDraw() {}
};

#endif
