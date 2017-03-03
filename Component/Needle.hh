#ifndef NEEDLE_HH_
# define NEEDLE_HH_

#include "OnTouch.hh"

/**
 * @brief @a OnTouch for explose the bomb
 */
class	OnTouchNeedle : public OnTouchBlock
{
public:
  /**
   * @brief the basic contructor
   */
  OnTouchNeedle() {}

  /**
   * @brief the load contructor
   */
  OnTouchNeedle(std::istream &) {}

  /**
   * @return true
   * @brief check if can be touch
   */
  virtual bool		canBeTouch(Entity const&) const;

  /**
   * @return false
   * @brief of target has bombExplode destroy it
   */
  virtual bool		getTouchBy(Entity &);
  virtual ~OnTouchNeedle() {}
};

#endif /* !NEEDLE_HH_ */
