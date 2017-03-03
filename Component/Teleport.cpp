#include "Teleport.hh"
#include "TeleportCenter.hh"
#include "Entity.hpp"
#include "Position.hh"

Teleport::Teleport()
{
  TeleportCenter::addTeleport(this);
}

Teleport::Teleport(std::istream &)
{
  TeleportCenter::addTeleport(this);
}

bool	Teleport::canBeTouch(Entity const&) const
{
  return (true);
}

Position	*Teleport::getLocation() const
{
  return (_owner->getComponent<Position>());
}

bool		Teleport::getTouchBy(Entity &target)
{
  Position	*pos;
  Position	*posto;
  Teleport	*next;

  if ((pos = target.getComponent<Position>()) &&
      (next = TeleportCenter::getNextTeleport(this)) &&
      (posto = next->getLocation()))
    {
      pos->getPos() = posto->getPos();
    }
  return (true);
}
void	Teleport::saveSelf(std::ostream& os) const
{
  os << "Teleport" << std::endl;
}

Teleport::~Teleport()
{
  TeleportCenter::removeTeleport(this);
}
