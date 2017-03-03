/**
 * @file Move.hh
 */
#ifndef MOVE_H_
# define MOVE_H_

# include <glm/glm.hpp>
# include "AComponent.hh"
# include "Position.hh"

/**
 * @class AMove
 * @brief Component that allows Entity to be moved
 */
class	AMove : public AComponent
{
protected:
  /**
   * @var _angle
   * @brief angle the Entity is facing
   */
  float		_angle;
public:
  AMove() : _angle(0) {}

  /**
   **@fn getAngle
   **@brief against all odds, this function gets the angle.
   */
  float	getAngle() const {return _angle;}

  /**
   **@fn move
   **@brief makes you move...
   */
  virtual bool	move(float angle, float deplace) = 0;
  virtual ~AMove() {}
};

/**
 **@class Move
 **@brief a class to deal with moving and trytouch
 */
class	Move : public AMove
{
private:

  /**
   **@class TryTouch
   **@brief to see of you can pass through walls or not...
   */
  class		TryTouch
  {
    Entity	*_self;

    /**
     **@var _canMove
     **@brief see function below.
     */
    bool	_canMove;
  public:
    TryTouch(Entity *self) : _self(self), _canMove(true) {}
    void	operator()(Entity *entity);

    /**
     **@fn canMove
     **@brief if you can move. no shit.
     */
    bool	canMove() const {return _canMove;}
  };
  bool		tryMove(Position *pos, glm::vec3 const &);
public:
  Move() {}
  Move(std::istream & is) { is >> _angle;}

  /**
   **@fn saveSelf
   **@brief save oneself for loading
   */
  virtual void saveSelf(std::ostream &os) const;

  /**
   **@fn move
   **@brief make you moooove. Incredible.
   */
  virtual bool move(float angle, float deplace);
  virtual ~Move() {}
};

/**
 * @class Moveable
 * @brief Component that allows Entity to move itself
 */
class	Moveable : public AUpdateComponent
{
  float	_speed;
public:
  Moveable() : _speed(0) {}
  Moveable(std::istream & is) { is >> _speed; }

  /**
   **@fn saveSelf
   **@brief such saving. very loading. wow.
   */
  virtual void saveSelf(std::ostream &os) const;
  virtual void update(gdl::Clock const &clock, gdl::Input &input);
  virtual ~Moveable() {}
};

#endif /* !MOVE_H_ */
