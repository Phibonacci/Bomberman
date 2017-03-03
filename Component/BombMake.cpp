#include "Position.hh"
#include "HasPlayer.hh"
#include "BombMake.hh"
#include "Entity.hpp"
#include "LifeTimer.hh"
#include "Hitbox.hh"
#include "Destruction.hh"
#include "Position.hh"
#include "Entity.hpp"
#include "HasPlayer.hh"
#include "OnTouch.hh"
#include "ModelDraw.hh"
#include "EntityFactory.hh"
#include "Board.hh"
#include "Part.hh"
#include <iostream>

void	BombMake::saveSelf(std::ostream& os) const
{
  os << "BombMake " << std::endl;
}

void	BombMaker::saveSelf(std::ostream& os) const
{
  os << "BombMaker " << _coolDown << std::endl;
}

void		BombMake::TryPutBomb::operator()(Entity *target)
{
  if (target->getComponent<LifeTimer>())
    {
      _canPutBomb = false;
    }
}

void		BombMake::makeBomb()
{
  Position	*pos;
  HasPlayer	*playerct;

  if ((pos = _owner->getComponent<Position>()) &&
      (playerct = _owner->getComponent<HasPlayer>()))
    {
      makeBomb(playerct->getPlayer());
    }
}

void		BombMake::makeBomb(Player *player)
{
  Position	*pos;
  Part		*part;
  Entity*	bomb;

  if ((pos = _owner->getComponent<Position>()) && player->getBombCount() > 0)
    {
      glm::vec3	const&	p(pos->getPos());

      if (player->getBombType() == BombType::NORMAL)
	{
	   bomb = EntityFactory::NewBomb
	    (pos->getBoardIn(),
	     glm::vec3(static_cast<int>(p.x + 0.5),
		       static_cast<int>(p.y + 0.5),
		       static_cast<int>(p.z + 0.5)), player);
	}
      else
	{
	  player->setBombRange();
	  bomb = EntityFactory::PierceBomb
	    (pos->getBoardIn(),
	     glm::vec3(static_cast<int>(p.x + 0.5),
		       static_cast<int>(p.y + 0.5),
		       static_cast<int>(p.z + 0.5)), player);
	}

      if ((part = (pos->getBoardIn())->find_part(pos->getPos())))
	{
	  std::list<Entity*>	collides;

	  part->collide(bomb, collides);
	  if (std::for_each(collides.begin(), collides.end(), TryPutBomb()).isOk())
	    {
	      pos->getBoardIn()->addEntity(bomb);
	      player->getBombCount() -= 1;
	      return ;
	    }
	}
      delete bomb;
    }
}

void		BombMaker::update(gdl::Clock const &clock, gdl::Input &)
{
  HasPlayer	*playerct;
  BombMake	*make;

  if ((playerct = _owner->getComponent<HasPlayer>())
      && (make = _owner->getComponent<BombMake>()))
    {
      if (_coolDown > 0)
	_coolDown -= clock.getElapsed();
      if (_coolDown <= 0 && playerct->getPlayer() && playerct->getPlayer()->getControl()
	  && playerct->getPlayer()->getControl()->getBut() == Controller::BUTTON_PUTBOMB)
	{
	  make->makeBomb(playerct->getPlayer());
	  _coolDown = 0.2;
	}
    }
}
