# include "ComponentFactory.hh"
# include "Position.hh"
# include "BombMake.hh"
# include "BombType.hh"
# include "Bonus.hh"
# include "Destruction.hh"
# include "HasBonus.hh"
# include "HasPlayer.hh"
# include "Hitbox.hh"
# include "LifeTimer.hh"
# include "ModelDraw.hh"
# include "MoveWall.hpp"
# include "Move.hh"
# include "CanKick.hh"
# include "OnDestroy.hh"
# include "EditMake.hpp"
# include "Needle.hh"
# include "Position.hh"
# include "Teleport.hh"
# include "RotateDraw.hh"
# include "Except.hpp"

template <typename T>
static AComponent *create(std::istream &is)
{
  return (new T(is));
}

std::string const	ComponentFactory::components[] =
  {
    "Position",
    "BombMake",
    "BombMaker",
    "Pierce",
    "SpeedModify",
    "RangeBombModify",
    "NumBombModify",
    "Skull",
    "CanKick",
    "GetKicked",
    "OnTouchBeKick",
    "BombExplode",
    "HasBonus",
    "HasPlayer",
    "Hitbox",
    "LifeTimer",
    "ModelDraw",
    "GeometryDraw",
    "Move",
    "WallMoveable",
    "Moveable",
    "Explosimble",
    "Explosible",
    "Explosiblock",
    "Explosicore",
    "OnTouchBlock",
    "OnTouchFire",
    "OnTouchNeedle",
    "RotateDraw",
    "KickShoe",
    "Teleport",
    "BeforeTp"
  };

ComponentFactory::t_creator const	ComponentFactory::creators[] =
  {
    ::create<Position>,
    ::create<BombMake>,
    ::create<BombMaker>,
    ::create<Pierce>,
    ::create<SpeedModify>,
    ::create<RangeBombModify>,
    ::create<NumBombModify>,
    ::create<Skull>,
    ::create<CanKick>,
    ::create<GetKicked>,
    ::create<OnTouchBeKick>,
    ::create<BombExplode>,
    ::create<HasBonus>,
    ::create<HasPlayer>,
    ::create<Hitbox>,
    ::create<LifeTimer>,
    ::create<ModelDraw>,
    ::create<GeometryDraw>,
    ::create<Move>,
    ::create<WallMoveable>,
    ::create<Moveable>,
    ::create<Explosimble>,
    ::create<Explosible>,
    ::create<Explosiblock>,
    ::create<Explosicore>,
    ::create<OnTouchBlock>,
    ::create<OnTouchFire>,
    ::create<OnTouchNeedle>,
    ::create<RotateDraw>,
    ::create<KickShoe>,
    ::create<Teleport>,
    ::create<BeforeTp>
  };

AComponent *ComponentFactory::create(std::string const& str,
				     std::istream &is)
{
  unsigned int	i;

  i = 0;
  while (i < sizeof(components) / sizeof(*components))
    {
      if (str == components[i])
	return ((creators[i])(is));
      ++i;
    }
  throw BombermanException("Not found component " + str);
  return (NULL);
}
