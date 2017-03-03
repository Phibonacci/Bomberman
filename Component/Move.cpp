#include <math.h>
#include "Move.hh"
#include "Position.hh"
#include "HasPlayer.hh"
#include "Entity.hpp"
#include "ModelDraw.hh"
#include "OnTouch.hh"

void	Move::saveSelf(std::ostream &os) const
{
  os << "Move " << _angle << std::endl;
}

void	Moveable::saveSelf(std::ostream &os) const
{
  os << "Moveable " << _speed << std::endl;
}

void		Move::TryTouch::operator()(Entity *target)
{
  OnTouch	*touch;
  bool		able;

  if ((touch = target->getComponent<OnTouch>()))
    {
      if ((able = touch->canBeTouch(*_self)))
	{
	  able = touch->getTouchBy(*_self);
	}
      _canMove = (_canMove && able);
    }
}

bool		Move::tryMove(Position *pos, glm::vec3 const& diff)
{
  Board			*map;
  Part			*part[2];
  std::list<Entity*>	collide_objs[2];
  glm::vec3 const	pos_bkup(pos->getPos());

  if (diff.x >= -0.0001 && diff.x <= 0.0001 &&
      diff.z >= -0.0001 && diff.z <= 0.0001)
    return (false);
  if ((map = pos->getBoardIn()) &&
      (part[0] = map->find_part(pos->getPos())) &&
      (part[1] = map->find_part(pos->getPos() + diff)))
    {
      part[0]->collide(_owner, collide_objs[0]);
      pos->getPos() += diff;
      part[1]->collide(_owner, collide_objs[1], collide_objs[0]);

      if (std::for_each(collide_objs[1].begin(), collide_objs[1].end(),
			TryTouch(_owner)).canMove())
	{
	  if (map->find_part(pos->getPos()) && part[0] != map->find_part(pos->getPos()))
	    {
	      part[0]->removeEntity(_owner);
	      map->find_part(pos->getPos())->addEntity(_owner);
	    }
	  return (true);
	}
      else
	pos->getPos() = pos_bkup;
    }
  return (false);
}

bool		Move::move(float angle, float deplace)
{
  float dx = deplace * sin(angle * M_PI / 180);
  float dy = deplace * cos(angle * M_PI / 180);
  Position	*pos;

  _angle = angle;
  pos = _owner->getComponent<Position>();
  return (tryMove(pos, glm::vec3(dx, 0, dy)) ||
	  tryMove(pos, glm::vec3(dx, 0, 0)) ||
	  tryMove(pos, glm::vec3(0, 0, dy)));
}

void		Moveable::update(gdl::Clock const &clock, gdl::Input &)
{
  HasPlayer	*hasplayer;
  Controller::IControl	*control;
  AMove		*methodmove;
  ModelDraw	*model;

  if ((hasplayer = _owner->getComponent<HasPlayer>()) &&
      (methodmove = _owner->getComponent<AMove>()) &&
      (hasplayer->getPlayer()) && (control = (hasplayer->getPlayer())->getControl()))
    {
      if (control->getDir().getSpeed() > 0)
	{
	  methodmove->move(control->getDir().getAngle(),
			   control->getDir().getSpeed() * clock.getElapsed()
			   * hasplayer->getPlayer()->getSpeed());
	}
      if ((model = _owner->getComponent<ModelDraw>()))
      	{
      	  if (control->getDir().getSpeed() > 0 && _speed == 0)
      	    model->setCurrentAnime("running");
      	  else if (_speed > 0 && control->getDir().getSpeed() == 0)
      	    model->setCurrentAnime("standing");
      	  _speed = control->getDir().getSpeed();
      	}
    }
}
