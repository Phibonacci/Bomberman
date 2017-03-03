#include "MoveWall.hpp"
#include "Entity.hpp"
#include "Move.hh"

WallMoveable::WallMoveable()
  : _angle(90)
{
}

WallMoveable::WallMoveable(std::istream& is)
{
  is >> _angle;
}

void	WallMoveable::saveSelf(std::ostream &os) const
{
  os << "WallMoveable " << _angle;
}

void	WallMoveable::update(gdl::Clock const &clock, gdl::Input &)
{
  Move		*methodmove;

  if ((methodmove = _owner->getComponent<Move>()))
    {
      if (!methodmove->move(_angle, clock.getElapsed() * 2.0))
	{
	  _angle += 90;
	  if (_angle > 360)
	    _angle -= 360;
	}
    }
}
