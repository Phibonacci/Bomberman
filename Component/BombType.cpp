#include "BombType.hh"

void	Pierce::saveSelf(std::ostream & os) const
{
  os << "Pierce " << canPierce << std::endl;
}
