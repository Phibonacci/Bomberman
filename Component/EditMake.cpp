#include "HasPlayer.hh"
#include "Entity.hpp"
#include "EditMake.hpp"
#include "Hitbox.hh"
#include "OnTouch.hh"
#include "EntityFactory.hh"
#include "Board.hh"
#include "Part.hh"
#include "ModelDraw.hh"
#include "DrawComponent.hh"
#include "ModelDrawLarger.hh"
#include "Position.hh"

void	EditMake::saveSelf(std::ostream &) const
{
}

void	EditMaker::saveSelf(std::ostream &) const
{
}

static std::map<EditMake::TWall, EditMake::fnct>	init_map()
{
  std::map<EditMake::TWall, EditMake::fnct>	mappy;

  mappy[EditMake::WALL] = &EntityFactory::NewBlock;
  mappy[EditMake::INDE] = &EntityFactory::NewUndestructibleBlock;
  mappy[EditMake::MOVE] = &EntityFactory::NewUndestructibleBlock;
  mappy[EditMake::TELEPORT] = &EntityFactory::NewTeleportBlock;
  mappy[EditMake::DEL] = &EntityFactory::DeleteBlock;
  return (mappy);
}

std::map<EditMake::TWall, EditMake::fnct> EditMake::_map = init_map();

int		&EditMake::getVal()
{
  return _val;
}

void		EditMake::makeWall(Player *, MapEditor& _edit)
{
  Position	*pos;
  Part		*part;

  if ((pos = _owner->getComponent<Position>()))
    {
      glm::vec3	const&	p(pos->getPos());
      Entity* bomb;
      glm::vec3 vec = glm::vec3(static_cast<int>(p.x + 0.5),
				static_cast<int>(p.y + 0.5),
				static_cast<int>(p.z + 0.5));
      HasPlayer *hplay;
      if (pos->getBoardIn()->findBlock(vec)
	  && (hplay = pos->getBoardIn()->findBlock(vec)->getComponent<HasPlayer>()))
	_edit.getPlayerList().remove(hplay->getPlayer());
      if (static_cast<EditMake::TWall>(_val) < EditMake::PLAYER)
	{
	  bomb = EditMake::_map[static_cast<EditMake::TWall>(_val)]
	    (pos->getBoardIn(),
	     vec, (static_cast<EditMake::TWall>(_val) == EditMake::MOVE ? Info::WALL : Info::NONE));
	}
      else
	{
	  Player *player = new Player((static_cast<EditMake::TWall>(_val)
				       == EditMake::PLAYER ? true : false));
	  bomb = EntityFactory::NewPlayer
	    (pos->getBoardIn(),
	     vec, player);
	  _edit.getPlayerList().push_back(player);
	  if (static_cast<EditMake::TWall>(_val) != EditMake::PLAYER)
	    {
	      _edit.getNai() += 1;
	    }
	}
      if (bomb && bomb != reinterpret_cast<Entity*>(-1)
	  && (part = (pos->getBoardIn())->find_part(pos->getPos())))
	{
	  std::list<Entity*>	collides;

	  part->collide(bomb, collides);
	  pos->getBoardIn()->addEntity(bomb);
	}
    }
}

void		EditMake::clearMap()
{
  Position*	pos;

  if ((pos = _owner->getComponent<Position>()))
    pos->getBoardIn()->clear();
}

void		EditMaker::changeDrawComponent(Player *& player, int val)
{
  std::map<EditMake::TWall, std::string>	tab;
  static maRand					random;

  tab[EditMake::WALL] = "Wall";
  tab[EditMake::INDE] = "UnWall";
  tab[EditMake::MOVE] = "BonusSpeed";
  tab[EditMake::TELEPORT] = "Teleport";
  tab[EditMake::DEL] = "Skull";
  player->getPerson()->removeComponent<ADrawComponent>();
  if (static_cast<EditMake::TWall>(val) < EditMake::PLAYER)
    {
      player->getPerson()->
	addComponent(new GeometryDraw(tab[static_cast<EditMake::TWall>(val)]));
    }
  else
    {
      float r[3];
      r[0] = random.getRand(0, 100) / 100.0f;
      r[1] = random.getRand(0, 100) / 100.0f;
      r[2] = random.getRand(0, 100) / 100.0f;
      player->getPerson()->addComponent(new ModelDraw("Bomberman"));
      player->getColor() = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
      if (static_cast<EditMake::TWall>(val) == EditMake::PLAYER)
	player->getColor() = glm::vec4(r[0], r[1], r[2], 1.0f);
    }
}

void		EditMaker::update(gdl::Clock const &clock, gdl::Input &)
{
  HasPlayer	*playerct;
  EditMake	*make;

  if ((playerct = _owner->getComponent<HasPlayer>())
      && (make = _owner->getComponent<EditMake>()))
    {
      if (_coolDown > 0)
	_coolDown -= clock.getElapsed();
      if (_coolDown <= 0 &&
	  playerct->getPlayer()->getControl()->getBut() == Controller::BUTTON_PUTBOMB)
	{
	  make->makeWall(playerct->getPlayer(), _edit);
	  _coolDown = 0.09f;
	}
      else if (_coolDown <= 0 &&
	  playerct->getPlayer()->getControl()->getBut() == Controller::BUTTON_MODE)
	{
	  make->getVal() += 1;
	  make->getVal() %= EditMake::MAX;
	  changeDrawComponent(playerct->getPlayer(), make->getVal());
	  _coolDown = 0.3f;
	}
      else
	{
	  if (_coolDown <= 0 &&
	      playerct->getPlayer()->getControl()->getBut() == Controller::BUTTON_X)
	    {
	      make->clearMap();
	      _coolDown = 0.1;
	    }
	}
    }
}
