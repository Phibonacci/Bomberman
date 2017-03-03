#include "Needle.hh"
#include "Destruction.hh"
#include "Entity.hpp"

bool	OnTouchNeedle::canBeTouch(Entity const&) const
{
  return (true);
}

bool	OnTouchNeedle::getTouchBy(Entity & target)
{
  if (target.getComponent<BombExplode>())
    {
      target.setDestroyed();
      return (false);
    }
  return (false);
}
