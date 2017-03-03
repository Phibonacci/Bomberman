#include "Position.hh"
#include "SaveLoad.hh"

void	Position::saveSelf(std::ostream & os) const
{
  os << "Position ";
  SaveLoad::saveVec3(os, _position);
  os << std::endl;
}

Position::Position(std::istream &is)
  : _map(NULL), _position(0, 0, 0)
{
  GameParty const	*current;

  if ((current = SaveLoad::getCurrent()))
    {
      _map = current->getBoard();
    }
  SaveLoad::loadVec3(is, _position);
}
