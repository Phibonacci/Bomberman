#include "EntityFactory.hh"
#include "Entity.hpp"
#include "ModelDraw.hh"
#include "Move.hh"
#include "Position.hh"
#include "HasPlayer.hh"
#include "LifeTimer.hh"
#include "Hitbox.hh"
#include "OnTouch.hh"
#include "Destruction.hh"
#include "BombMake.hh"
#include "MapLoader.hh"
#include "Bonus.hh"
#include "OnDestroy.hh"
#include "HasBonus.hh"
#include "BombType.hh"
#include "maRand.hh"
#include "CanKick.hh"
#include "EditMake.hpp"
#include "Needle.hh"
#include "MoveWall.hpp"
#include "Teleport.hh"
#include "RotateDraw.hh"

template<class T>
const std::string	EntityFactory::selectBonusOrMalus(Entity * bonus, int var, int rate,
							  const std::string strBonus, const std::string strMalus)
{
  if (var < rate && var % 2)
    {
      bonus->addComponent(new T(-1));
      return (strMalus);
    }
  else
    {
      bonus->addComponent(new T(1));
      return (strBonus);
    }
  return (strBonus);
}

const std::string	EntityFactory::selectBonus(Entity * bonus, int i)
{
  static maRand		random;
  int			var = 12;

  var = random.getRand(0, 100);

  i /= 10;
  if (i >= 1 && i <= 3)
    {
      return (selectBonusOrMalus<RangeBombModify>(bonus, var, 30, "BonusRange", "MalusRange"));
    }
  else if (i > 3 && i <= 6)
    {
      return (selectBonusOrMalus<NumBombModify>(bonus, var, 30, "BonusStock", "MalusStock"));
    }
  else
    {
      return (selectBonusOrMalus<SpeedModify>(bonus, var, 30, "BonusSpeed", "MalusSpeed"));
    }
  return (selectBonusOrMalus<RangeBombModify>(bonus, var, 30, "BonusRange", "MalusRange"));
}

int		EntityFactory::isASpecialBonus(Entity *bonus, int var)
{
  if (var < 0)
    var *= -1;

  if (var == 12 || var == 22 || var == 32 || var == 52)
    {
      bonus->addComponent(new RotateDraw("KickBomb"));
      bonus->addComponent(new KickShoe);
      return (2);
    }
  else if (var == 84 || var == 42)
    {
      if (var == 84)
	{
	  bonus->addComponent(new Skull(-1));
	  bonus->addComponent(new RotateDraw("Skull"));
	  return (2);
	}
      else
	{
	  bonus->addComponent(new RotateDraw("PierceBomb"));
	  bonus->addComponent(new Pierce);
	  return (2);
	}
    }
  else
    {
      if ((var % 20) == 0)
	return (1);
    }
  return (3);
}

Entity* EntityFactory::NewBlock(Board *board, glm::vec3 const& vec, Info::Mod mod)
{
  if (board->findBlock(vec))
    if (EntityFactory::DeleteBlock(board, vec) == reinterpret_cast<Entity*>(-1))
      return (NULL);

  static maRand		random;
  Entity* rt = new Entity;
  int var;

  var = random.getRand(0, 100);
  rt->addComponent(new Position(board, vec));
  rt->addComponent(new GeometryDraw("Wall"));
  rt->addComponent(new Hitbox(glm::vec3(0.9, 0.9, 0.9)));
  rt->addComponent(new Explosiblock);
  rt->addComponent(new OnTouchBlock);

  if (!(var % 2))
    {
      Entity*	bonus = new Entity;
      int	select = 0;

      select = isASpecialBonus(bonus, var);

      if (select == 1 && mod == Info::TELEPORT)
	{
	  delete bonus;
	  bonus = NewBeforeTpBlock();
	}
      else
	{
	  if (select != 2)
	    bonus->addComponent(new RotateDraw(selectBonus(bonus, var)));
	  bonus->addComponent(new Hitbox(glm::vec3(0.6, 0.6, 0.6)));
	  bonus->addComponent(new RangeBombModify(1));
	  bonus->addComponent(new Explosible);
	}

      rt->addComponent(new HasBonus(bonus));
    }
  return rt;
}

Entity* EntityFactory::DeleteBlock(Board *board, glm::vec3 const& vec, Info::Mod)
{
  Entity*	toDel = board->findBlock(vec);
  Position	*pos;

  if (toDel && (pos = toDel->getComponent<Position>()))
    {
      if (pos->getPos().x != 0.0f && pos->getPos().x != board->getWidth() - 1
	  && pos->getPos().z != 0.0f && pos->getPos().z != board->getHeight() - 1)
	{
	  board->removeEntity(toDel);
	}
      else
	return (reinterpret_cast<Entity*>(-1));
    }
  return (NULL);
}

Entity* EntityFactory::NewBeforeTpBlock()
{
  Entity* rt = new Entity;
  rt->addComponent(new BeforeTp);
  return rt;
}

Entity* EntityFactory::NewTeleportBlock(Board *board,
					glm::vec3 const& vec, Info::Mod)
{
  if (board->findBlock(vec))
    if (EntityFactory::DeleteBlock(board, vec) == reinterpret_cast<Entity*>(-1))
      return (NULL);
  Entity* rt = new Entity;
  rt->addComponent(new Position(board, vec));
  rt->addComponent(new Teleport);
  rt->addComponent(new ModelDraw("TP"));
  rt->addComponent(new Hitbox(glm::vec3(0.9, 0.9, 0.9)));
  return rt;
}

Entity* EntityFactory::NewUndestructibleBlock(Board *board,
					      glm::vec3 const& vec, Info::Mod mod)
{
  static maRand		random;

  if (board->findBlock(vec))
    if (EntityFactory::DeleteBlock(board, vec) == reinterpret_cast<Entity*>(-1))
      return (NULL);
  Entity* rt = new Entity;
  rt->addComponent(new Position(board, vec));
  rt->addComponent(new GeometryDraw("UnWall"));
  rt->addComponent(new OnTouchBlock);
  if (mod != Info::WALL)
    rt->addComponent(new Hitbox(glm::vec3(0.9, 0.9, 0.9)));
  if (mod == Info::WALL)
    {
      rt->addComponent(new Hitbox(glm::vec3(1.0, 1.0, 1.0)));
      if (vec.x != 0.0f && vec.x != board->getWidth() - 1
	  && vec.z != 0.0f && vec.z != board->getHeight() - 1)
	{
	  rt->addComponent(new CanKick);
	  rt->addComponent(new Move);
	  rt->addComponent(new WallMoveable);
	}
    }
  rt->addComponent(new OnTouchNeedle);
  rt->addComponent(new Explosimble);
  return rt;
}

Entity* EntityFactory::NewPlayer(Board *board, glm::vec3 const& vec,
				 Player* player, Info::Mod)
{
  if (board->findBlock(vec))
    if (EntityFactory::DeleteBlock(board, vec) == reinterpret_cast<Entity*>(-1))
      return (NULL);
  Entity* rt = new Entity;

  rt->addComponent(new Position(board, vec));
  rt->addComponent(new Move());
  rt->addComponent(new ModelDraw("Bomberman"));
  rt->addComponent(new HasPlayer(player, true));
  rt->addComponent(new Moveable);
  rt->addComponent(new Hitbox(glm::vec3(0.4, 0.4, 0.4)));
  rt->addComponent(new OnTouchBlock);
  rt->addComponent(new Explosicore(100));
  rt->addComponent(new BombMake);
  rt->addComponent(new BombMaker);
  return rt;
}

Entity* EntityFactory::NewEditPlayer(Board *board, glm::vec3 const& vec, Player* player)
{
  Entity* rt = new Entity;

  rt->addComponent(new Position(board, vec));
  rt->addComponent(new Move());
  rt->addComponent(new ModelDraw("Wall"));
  rt->addComponent(new HasPlayer(player, true));
  rt->addComponent(new Moveable);
  rt->addComponent(new Hitbox(glm::vec3(0.4, 0.4, 0.4)));
  rt->addComponent(new Explosible);
  return rt;
}

#include "ModelDrawLarger.hh"

Entity* EntityFactory::NewBomb(Board *board, glm::vec3 const& vec, Player *player)
{
  Entity *bomb = new Entity;

  bomb->addComponent(new Position(board, vec));
  bomb->addComponent(new LifeTimer(3.0f));
  bomb->addComponent(new Hitbox(glm::vec3(0.6, 0.6, 0.6)));
  bomb->addComponent(new BombExplode(player->getBombRange()));
  bomb->addComponent(new OnTouchBeKick);
  bomb->addComponent(new Explosible);
  bomb->addComponent(new Move());
  bomb->addComponent(new ModelDrawLarger("Bomb", 0.0005));
  bomb->addComponent(new HasPlayer(player));
  return (bomb);
}

Entity* EntityFactory::PierceBomb(Board *board, glm::vec3 const& vec, Player *player)
{
  Entity *bomb = new Entity;

  bomb->addComponent(new Position(board, vec));
  bomb->addComponent(new LifeTimer(3.0f));
  bomb->addComponent(new Hitbox(glm::vec3(0.6, 0.6, 0.6)));
  bomb->addComponent(new BombExplode(player->getBombRange()));
  bomb->addComponent(new Move());
  bomb->addComponent(new OnTouchBeKick);
  bomb->addComponent(new Explosible);
  bomb->addComponent(new Pierce);
  bomb->addComponent(new ModelDrawLarger("Bomb", 0.0005));
  bomb->addComponent(new ModelDraw("Bomb"));
  bomb->addComponent(new HasPlayer(player));
  return (bomb);
}

Entity* EntityFactory::NewFire(Board *board, glm::vec3 const& pos, glm::vec3 const & hitbox)
{
  Entity	*explosion = new Entity;

  explosion->addComponent(new Position(board, pos));
  explosion->addComponent(new Hitbox(hitbox));
  explosion->addComponent(new OnTouchFire);
  return (explosion);
}
