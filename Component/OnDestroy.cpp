#include "Entity.hpp"
#include "BombType.hh"
#include "OnDestroy.hh"
#include "HasPlayer.hh"
#include "Player.hh"

void	Explosimble::saveSelf(std::ostream & os) const
{
  os << "Explosimble " << std::endl;
}

void	Explosible::saveSelf(std::ostream & os) const
{
  os << "Explosible " << std::endl;
}

void	Explosiblock::saveSelf(std::ostream & os) const
{
  os << "Explosiblock " << std::endl;
}

Explosicore::Explosicore(std::istream &is)
{
  is >> _score;
}

void	Explosicore::saveSelf(std::ostream &os) const
{
  os << "Explosicore " << _score <<std::endl;
}

bool		Explosiblock::blockDestroy(Entity const & entity) const
{
  if (entity.getComponent<Pierce>())
    return (true);
  return (false);
}

bool		Explosicore::blockDestroy(Entity const& target) const
{
  HasPlayer	*a;
  HasPlayer	*t;

  if ((a = target.getComponent<HasPlayer>()) &&
      (t = _owner->getComponent<HasPlayer>()))
    {
      if (a->getPlayer() != t->getPlayer())
	(a->getPlayer())->getScore() += _score;
      else
	(a->getPlayer())->getScore() -= _score;
    }
  return (true);
}
