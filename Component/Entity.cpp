#include "Position.hh"
#include "Entity.hpp"
#include "Hitbox.hh"
#include "Destruction.hh"
#include <algorithm>
#include "ComponentFactory.hh"
#include "Except.hpp"

bool		Entity::collide(Entity const& target) const
{
  Hitbox	*self;
  Hitbox	*op;

  if ((self = getComponent<Hitbox>()) &&
      (op = target.getComponent<Hitbox>()))
    {
      return (self->isInTouch(*op));
    }
  return (false);
}

void		Entity::setDestroyed()
{
  Position	*pos;
  Board		*board;

  if (!_needDestroy)
    {
      if ((pos = getComponent<Position>()) &&
	  (board = pos->getBoardIn()))
	{
	  board->removeEntity(this);
	}
      else
	{
	  throw BombermanException("Cant destroy entity");
	}
    }
  _needDestroy = true;
}

Entity&		Entity::addComponent(AComponent *compo)
{
  AUpdateComponent	*update;
  ADrawComponent	*draw;

  if (compo) {
    compo->setOwner(this);
    _components.push_back(compo);
    if ((update = dynamic_cast<AUpdateComponent*>(compo)))
      _toupdate.push_back(update);
    if ((draw = dynamic_cast<ADrawComponent*>(compo)))
      _todraw.push_back(draw);
  }
  return *this;
}

void		Entity::onDestroy()
{
  ADestruction	*destroy;

  if ((destroy = getComponent<ADestruction>()))
    {
      destroy->destroy();
    }
}

void		Entity::Saver::operator()(AComponent *target)
{
  target->saveSelf(_os);
}

void		Entity::saveSelf(std::ostream &os)
{
  if (!_needDestroy)
    {
      os << "<Entity" << std::endl;
      std::for_each(_components.begin(), _components.end(), Saver(os));
      os << "Entity>" << std::endl;
    }
}

Entity::Entity(std::istream &is)
  : _needDestroy(false)
{
  while (!is.eof())
    {
      std::string	str;

      is >> str;
      if (str == "Entity>")
	break ;
      addComponent(ComponentFactory::create(str, is));
    }
}
