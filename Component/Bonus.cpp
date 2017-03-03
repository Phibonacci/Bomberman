#include "Bonus.hh"
#include "HasPlayer.hh"
#include "Entity.hpp"
#include "maRand.hh"
#include "CanKick.hh"

/*
** save self
*/
void	RangeBombModify::saveSelf(std::ostream & os) const
{
  os << "RangeBombModify " << _modify << std::endl;
}

void	SpeedModify::saveSelf(std::ostream & os) const
{
  os << "SpeedModify " << _modify << std::endl;
}

void	NumBombModify::saveSelf(std::ostream & os) const
{
  os << "NumBombModify " << _modify << std::endl;
}

void	Skull::saveSelf(std::ostream & os) const
{
  os << "Skull " << _modify << std::endl;
}

void	KickShoe::saveSelf(std::ostream & os) const
{
  os << "KickShoe" << std::endl;
}

/*
** Bonus
*/
bool RangeBombModify::getTouchBy(Entity &entity)
{
  HasPlayer	*player;

  if ((player = entity.getComponent<HasPlayer>()))
    {
      if ((_modify < 0 && player->getPlayer()->getBombRange() > 1))
	player->getPlayer()->getBombRange() += _modify;
      else if ((_modify > 0 && player->getPlayer()->getBombRange() <= 5))
	player->getPlayer()->getBombRange() += _modify;
    }
  _owner->setDestroyed();
  return true;
}

bool SpeedModify::getTouchBy(Entity &entity)
{
  HasPlayer	*player;

  if ((player = entity.getComponent<HasPlayer>()))
    {
      if (_modify > 0 && player->getPlayer()->getSpeed() < 6.0f)
	player->getPlayer()->getSpeed() += _modify;
      else if (_modify < 0 && player->getPlayer()->getSpeed() >= 3.0f)
	player->getPlayer()->getSpeed() += _modify;
    }
  _owner->setDestroyed();
  return true;
}

bool NumBombModify::getTouchBy(Entity &entity)
{
  HasPlayer	*player;

  if ((player = entity.getComponent<HasPlayer>()))
    {
      if (_modify > 0 && player->getPlayer()->getBombCount() < 5)
	player->getPlayer()->getBombCount() += _modify;
      else if (_modify < 0 && player->getPlayer()->getBombCount() > 1)
	player->getPlayer()->getBombCount() += _modify;

    }
  _owner->setDestroyed();
  return true;
}

bool Skull::getTouchBy(Entity &entity)
{
  HasPlayer	*player;

  if ((player = entity.getComponent<HasPlayer>()))
    {
      player->getPlayer()->getBombRange() = 1;
      player->getPlayer()->getSpeed() = 3.0f;
      player->getPlayer()->getBombCount() = 1;
      player->getPlayer()->setBombType(BombType::NORMAL);
    }
  _owner->setDestroyed();
  return true;
}

bool		KickShoe::getTouchBy(Entity &entity)
{
  CanKick	*kick;
  HasPlayer	*player;

  if ((player = entity.getComponent<HasPlayer>()))
    {
      if (!(kick = entity.getComponent<CanKick>()))
	{
	  kick = new CanKick;
	  entity.addComponent(kick);
	}
    }
  _owner->setDestroyed();
  return (true);
}
