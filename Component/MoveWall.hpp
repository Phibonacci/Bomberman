#ifndef __MOVEWALL_HPP__
# define __MOVEWALL_HPP__

# include "AComponent.hh"
# include "Position.hh"
# include "OnTouch.hh"

class Entity;

/**
 **@class WallMoveable
 **@brief a class to deal withall those pesky moving walls. Feels like Hogwarth's men.
 */
class	WallMoveable : public AUpdateComponent
{
  float	_angle;
public:
  /**
   **@brief first constructor
   */
  WallMoveable();

  /**
   **@brief second constructor
   */
  WallMoveable(std::istream &);

  /**
   **@fn saveSelf
   **@brief saves the entity
   */
  virtual void saveSelf(std::ostream &os) const;
  virtual void update(gdl::Clock const &clock, gdl::Input &input);
  virtual ~WallMoveable(){}
};

#endif // !__MOVEWALL_HPP__
