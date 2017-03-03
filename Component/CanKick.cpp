#include "CanKick.hh"
#include "Position.hh"
#include "Move.hh"
#include "Entity.hpp"
#include "GameEngine.hh"
#include <math.h>

void	CanKick::saveSelf(std::ostream & os) const
{
  os << "CanKick" << std::endl;
}

void	GetKicked::saveSelf(std::ostream & os) const
{
  os << "GetKicked" << " " << _angle << " " << _speed << std::endl;
}

void	OnTouchBeKick::saveSelf(std::ostream &os) const
{
  os << "OnTouchBeKick" << std::endl;
}

bool		OnTouchBeKick::canBeTouch(Entity const& target) const
{
  CanKick	*k;

  if ((k = target.getComponent<CanKick>())
      || target.getComponent<OnTouchBeKick>())
    {
      return (true);
    }
  return (false);
}

bool		OnTouchBeKick::getTouchBy(Entity & target)
{
  Position	*self;
  Position	*op;
  GetKicked	*kick = NULL;
  CanKick	*cankick = NULL;

  if ((self = _owner->getComponent<Position>()) &&
      (op = target.getComponent<Position>()))
    {
      if ((cankick = target.getComponent<CanKick>()))
	{
	  glm::vec3 diff(self->getPos() - op->getPos());

	  float angle;
	  if (ABS(diff.z) > ABS(diff.x))
	    angle = 90 - 90 * (ABS(diff.z) / diff.z);
	  else
	    angle = 90 * (ABS(diff.x) / diff.x);

	  if (kick)
	    kick->reinit(angle + 180, 4.0);
	  _owner->addComponent(new GetKicked(angle, 4.0));
	  return (false);
	}
    }
  return (false);
}

GetKicked::GetKicked(float angle, float speed)
  : _angle(angle), _speed(speed)
{
  GameEngine::_sound.zPlay(Zik::KICKBOMB);
}

void GetKicked::reinit(float angle, float speed)
{
  _angle = angle;
  _speed = speed;
}

float GetKicked::getSpeed() const
{
  return (_speed);
}

void GetKicked::update(gdl::Clock const &clock, gdl::Input &)
{
  AMove	*move;

  if (_speed && (move = _owner->getComponent<AMove>()))
    {
      if (move->move(_angle, _speed * clock.getElapsed()) == false)
	_speed = 0;
    }
}
