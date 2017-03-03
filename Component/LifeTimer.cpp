#include "LifeTimer.hh"
#include "Entity.hpp"

void	LifeTimer::saveSelf(std::ostream &os) const
{
  os << "LifeTimer " << _timeRest << std::endl;
}

void	LifeTimer::update(gdl::Clock const &clock, gdl::Input &)
  {
    _timeRest -= clock.getElapsed();
    if (_timeRest < 0)
      {
	_owner->setDestroyed();
      }
  }
