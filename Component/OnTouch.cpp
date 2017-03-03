#include "OnTouch.hh"
#include "Entity.hpp"
#include "HasPlayer.hh"
#include "BombType.hh"
#include <iostream>
#include "OnDestroy.hh"
#include "BombMake.hh"
#include "GameEngine.hh"

void	OnTouchBlock::saveSelf(std::ostream & os) const
{
  os << "OnTouchBlock " << std::endl;
}

void	OnTouchFire::saveSelf(std::ostream & os) const
{
  os << "OnTouchFire " << std::endl;
}

bool	OnTouchBlock::canBeTouch(Entity const&) const
{
  return (false);
}

bool	OnTouchBlock::getTouchBy(Entity &)
{
  return (false);
}

bool	OnTouchFire::getTouchBy(Entity &target)
{
  HasPlayer *pl;

  if (!target.getComponent<Explosimble>())
    target.setDestroyed();
  if ((pl = _owner->getComponent<HasPlayer>()))
    {
      OnDestroy		*touch;

      if ((touch = target.getComponent<OnDestroy>()) &&
	  touch->canBeDestroy(*_owner))
	{
	  touch->blockDestroy(*_owner);
	}
    }
  return (true);
}

bool	OnTouchCollect::canBeTouch(Entity const& target) const
{
   HasPlayer*	player = target.getComponent<HasPlayer>();

  if ((_owner->getComponent<Pierce>()) && (player))
    {
      player->getPlayer()->setBombType(BombType::PIERCE);
    }
  GameEngine::_sound.zPlay(Zik::ITEMGET);
  return true;
}
