#include "TeleportCenter.hh"
#include "Teleport.hh"
#include <algorithm>

std::list<Teleport*> TeleportCenter::_teleports;

void	TeleportCenter::addTeleport(Teleport *t)
{
  _teleports.push_back(t);
}

void	TeleportCenter::removeTeleport(Teleport *t)
{
  _teleports.remove(t);
}

Teleport * TeleportCenter::getNextTeleport(Teleport *t)
{
  std::list<Teleport*>::const_iterator	it =
    std::find(_teleports.begin(), _teleports.end(), t);

  if (it != _teleports.end() && (++it) != _teleports.end())
    return (*it);
  return (*_teleports.begin());
}
