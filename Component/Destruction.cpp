#include "Destruction.hh"
#include "Position.hh"
#include "Direction.hh"
#include "LifeTimer.hh"
#include "OnDestroy.hh"
#include "HasPlayer.hh"
#include "GameEngine.hh"
#include "Entity.hpp"
#include "ModelDraw.hh"
#include "OnTouch.hh"
#include "EntityFactory.hh"
#include "BombType.hh"

void	BombExplode::saveSelf(std::ostream& os) const
{
  os << "BombExplode " << _range << std::endl;
}

void	BombExplode::TryDestruct::operator()(Entity *target)
{
  OnDestroy	*touch;
  bool		able;

  if ((touch = target->getComponent<OnDestroy>()))
    {
      if ((able = touch->canBeDestroy(*_self)))
	{
	  target->setDestroyed();
	  able = touch->blockDestroy(*_self);
	}
      _canDestruct = (_canDestruct && able);
    }
}

BombExplode::Explosion::Explosion(unsigned int range,
				  Position const *pos,
				  Hitbox const *hit, Entity *owner)
  : _range(range), _owner(owner), _pos(pos), _hitbox(hit)
{
}

void		BombExplode::Explosion::chooseTexture(float dx, float dy, std::string & textureFire)
{
  if (dx == 0 && dy == 0)
    textureFire = "Fire_Cross";
  else if ((dy < 0 && dx == 0) ||
      (dy > 0 && dx == 0))
    textureFire = "Fire_Turn";
  else
    textureFire = "Fire";
}

const std::string 	BombExplode::Explosion::chooseSide(float value, const std::string  s1, const std::string  s2)
{
  if (value < 0)
    return (s1);
  return (s2);
}

void		BombExplode::Explosion::chooseEnd(float dx, float dy, std::string & textureFire)
{
  if (dx == 0)
    textureFire = chooseSide(dy, "Fire_EndUp", "Fire_EndDown");
  else if (dy == 0)
    textureFire = chooseSide(dx, "Fire_EndLeft", "Fire_EndRight");
  else
    textureFire = "Fire";
}

bool		BombExplode::Explosion::explodeArea(glm::vec3 const& pos, float dx, float dy)
{
  Part		*part;
  std::string	textureFire = "";
  HasPlayer	*putter;

  if ((part = (_pos->getBoardIn())->find_part(pos)))
    {
      std::list<Entity*>	collides;
      Entity			*explosion = EntityFactory::NewFire(_pos->getBoardIn(), pos, _hitbox->getSize());

      if ((putter = _owner->getComponent<HasPlayer>()))
	explosion->addComponent(new HasPlayer(putter->getPlayer()));
      if (_owner->getComponent<Pierce>())
	{
	  explosion->addComponent(new Pierce);
	}
      part->collide(explosion, collides);
      if (std::for_each(collides.begin(), collides.end(),
			TryDestruct(explosion)).canDestruct())
	{

	  if ((dy * -1) == _range || (dy) == _range
	      || (dx * -1) == _range || (dx) == _range) {

	    chooseTexture(dx, dy, textureFire);
	    chooseEnd(dx, dy, textureFire);
	    }
	  else {

	    chooseTexture(dx, dy, textureFire);
	    }

	    explosion->addComponent(new GeometryDraw(textureFire));

	  explosion->addComponent(new LifeTimer(0.4f));
	  (_pos->getBoardIn())->addEntity(explosion);
	  return (false);
	}
      else
	{
	  delete explosion;
	}
    }
  return (true);
}

void		BombExplode::Explosion::explode()
{
  bool		blocked[sizeof(Direction::all) /
			sizeof(*Direction::all)];
  glm::vec3 const&	position(_pos->getPos());

  if (_owner->getComponent<Pierce>())
    GameEngine::_sound.zPlay(Zik::SPIKEBOMB);
  else
    GameEngine::_sound.zPlay(Zik::NORMBOMB);
  for (size_t counter = 0;
       counter < sizeof(blocked) / sizeof(*blocked);
       ++counter)
    {
      blocked[counter] = false;
    }
  explodeArea(_pos->getPos(), 0, 0);
  for (float loc = 1; loc <= _range; ++loc)
    {
      for (size_t i = 0 ; i < sizeof(blocked) / sizeof(*blocked) ; ++i)
	{
	  if (!blocked[i])
	    {
	      int const * const dxdys =
		Direction::convert_to_cartesian(Direction::all[i]);
	      float	dx = static_cast<float>(dxdys[0]) * loc;
	      float	dy = static_cast<float>(dxdys[1]) * loc;

	      blocked[i] = explodeArea(glm::vec3(position.x + dx,
						 position.y,
						 position.z + dy),
				       dx, dy);
	    }
	}
    }
}

void		BombExplode::destroy()
{
  Position	*position;
  HasPlayer	*hasowner;
  Hitbox	*hitbox;

  if ((position = _owner->getComponent<Position>()) &&
      (hitbox = _owner->getComponent<Hitbox>()))
    {
      Explosion	explode(_range,
			position, hitbox, _owner);

      explode.explode();
      if ((hasowner = _owner->getComponent<HasPlayer>()))
	(hasowner->getPlayer())->getBombCount() += 1;
    }
}
