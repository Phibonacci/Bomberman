#include "HasBonus.hh"
#include "Position.hh"
#include "Entity.hpp"
#include "Position.hh"
#include "Info.hpp"
#include "EntityFactory.hh"
#include "Teleport.hh"

HasBonus::HasBonus(std::istream &is)
{
  std::string str;

  is >> str;
  if (str == "<Entity")
    {
      _bonus = new Entity(is);
    }
}

void	HasBonus::saveSelf(std::ostream & os) const
{
  os << "HasBonus ";
  _bonus->saveSelf(os);
}

void	HasBonus::destroy()
{
  Position	*pos;

  if (_bonus && (pos = _owner->getComponent<Position>()))
    {
      if (_bonus->getComponent<BeforeTp>())
	{
	  delete (_bonus);
	  _bonus = EntityFactory::NewTeleportBlock(pos->getBoardIn(),
						   pos->getPos(), Info::NONE);
	}
      else
	_bonus->addComponent(new Position(pos->getBoardIn(), pos->getPos()));
      if (!(pos->getBoardIn())->addEntity(_bonus))
	delete _bonus;
      _bonus = NULL;
    }
}

HasBonus::~HasBonus()
{
  if (_bonus)
    delete _bonus;
}
