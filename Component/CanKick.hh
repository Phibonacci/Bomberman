/**
 * @file CanKick.hh
 */
#ifndef CANKICK_H_
# define CANKICK_H_

# include "AComponent.hh"
# include "OnTouch.hh"
# include <istream>

/**
 * @class CanKick
 * @brief entity can kick
 */
class	CanKick : public AComponent
{
public:
  virtual ~CanKick() {}
  CanKick() {}
  CanKick(std::istream &) {}
  virtual void	saveSelf(std::ostream&) const;
};

/**
 * @class GetKicked
 * @brief entity was kicked
 */
class	GetKicked : public AUpdateComponent
{
  float	_angle;
  float	_speed;
public:
  GetKicked(float angle, float speed);
  GetKicked(std::istream & is) { is >> _angle >> _speed; }
  void	reinit(float angle, float speed);
  float getSpeed() const;
  virtual void update(gdl::Clock const &clock, gdl::Input &input);
  virtual ~GetKicked() {}
  virtual void	saveSelf(std::ostream&) const;
};

/**
 * @class OnTouchBeKick
 * @brief entity can be kicked
 */
class	OnTouchBeKick : public OnTouch
{
public:
  OnTouchBeKick() {};
  OnTouchBeKick(std::istream &) {};
  virtual bool		canBeTouch(Entity const&) const;
  virtual bool		getTouchBy(Entity &);
  virtual ~OnTouchBeKick() {}
  virtual void	saveSelf(std::ostream&) const;
};

#endif /* !CANKICK_H_ */
