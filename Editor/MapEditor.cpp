#include "MapEditor.hpp"
#include "GamePlayer.hh"
#include "MapLoader.hh"
#include "EntityFactory.hh"
#include "GameParty.hh"
#include "ModelDraw.hh"
#include "Player.hh"
#include "Menus.hh"
#include "BombMake.hh"
#include "EditMake.hpp"
#include "Hitbox.hh"
#include "MasterController.hpp"
#include "SaveLoad.hh"

MapEditor::MapEditor(GameParty *gp)
  : _gp(gp), _saveDelay(0), _nai(0), _str("")
{
}

MapEditor::~MapEditor()
{
}

void		MapEditor::initScreen(Screen::AScreen& scr)
{
  _gp->initScreen(scr);
}

void	MapEditor::initialize(Info& info)
{
  Controller::MasterController::restart();
  info.getNPlayers() = 1;
  info.getNAi() = 0;
  if (_gp->getBoard())
    {
      _gp->reinit();
    }
  _gp->initialize(info);
  _player = _gp->getPlayer(0);
  _player->getPerson()->removeComponent<Hitbox>();
  _player->getPerson()->removeComponent<ModelDraw>();
  _player->getPerson()->addComponent(new GeometryDraw("Wall"));
  _player->getPerson()->removeComponent<BombMake>();
  _player->getPerson()->addComponent(new EditMake);
  _player->getPerson()->removeComponent<BombMaker>();
  _player->getPerson()->addComponent(new EditMaker(*this));
  _player->getSpeed() += 4.0f;
}

int	MapEditor::update(gdl::Clock const& cl, gdl::Input& input)
{
  _player->getControl()->checkMove(input);
  _gp->getBoard()->update(cl, input);
  if (_saveDelay <= 0)
    _str = std::string();
  if (_player->getControl()->getBut() == Controller::BUTTON_START)
    {
      return (0);
    }
  if (_saveDelay <= 0
      && _player->getControl()->getBut() == Controller::BUTTON_BACK)
    {
      SaveLoad save(_gp);

      _saveDelay = 5;
      if ((static_cast<int>(_playerList.size() - _nai)) <= 0)
	{
	  _str = "no player on map";
	  return (3);
	}
      GamePlayer *gplayer = new GamePlayer(_playerList.size(), _nai);
      for (int i = 0 ; !_playerList.empty(); i++)
	{
	  gplayer->getPlayer(i) = _playerList.front();
	  _playerList.pop_front();
	}
      _gp->setGamePlayer(gplayer);
      _player->getPerson()->removeComponent<EditMaker>();
      EntityFactory::DeleteBlock(_gp->getBoard(),
				 _player->getPerson()->
				 getComponent<Position>()->getPos(), Info::NONE);
      _gp->getBoard()->update(cl, input);
      save.saveParty();
      return (0);
    }
  _saveDelay -= (_saveDelay > 0) * cl.getElapsed();
  return (3);
}

void	MapEditor::draw(Screen::AScreen& sc, gdl::Clock const& cl)
{
  _gp->draw(sc, cl);
  if (_str != "")
    DrawComponent::putsSubScreen(_str, glm::vec2(0, 0), sc,
				 *(sc.getScreens()[0]), glm::vec3(1, 1, 1));
}
