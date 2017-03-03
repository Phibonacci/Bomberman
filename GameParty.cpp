#include "GameParty.hh"
#include "Entity.hpp"
#include "Position.hh"
#include "MapLoader.hh"
#include <sstream>
#include "Bonus.hh"
#include "Menus.hh"
#include "AI.hh"
#include "IControl.hh"
#include "MasterController.hpp"
#include "ACamera.hh"
#include "DrawComponent.hh"
#include "ConfigLoader.hpp"
#include "ModelDraw.hh"
#include "SaveLoad.hh"
#include "Except.hpp"

float const	GameParty::victory_time = 5.0f;

GameParty::GameParty(Pause *pause)
{
  _board = NULL;
  _player = NULL;
  _pause = pause;
  _iACenter = NULL;
  _iAThread = NULL;
  _alive = 0;
  _saveDelay = 0;
}

Player		*GameParty::getPlayer(unsigned int idx) const
{
  return ((_player->getPlayer(idx)));
}

Player		*&GameParty::getPlayer(unsigned int idx)
{
  return ((_player->getPlayer(idx)));
}

Board		*&GameParty::getBoard()
{
  return _board;
}

void		GameParty::setBoard(Board *board)
{
  _board = board;
}

void		GameParty::setGamePlayer(GamePlayer *player)
{
  _player = player;
}

void		GameParty::start()
{
  Controller::Peripheral* periph;

 _saveDelay = 0;
 _waiting = victory_time;
 _iACenter = new GameIA(this);
 for (size_t i = 0 ; i < _player->getPlayerCount() - _player->getIACount(); i++)
   {
     if ((periph = Controller::MasterController::rtPeripheral()) == NULL)
       throw ExceptMap("no enough controller");
     _player->getPlayer(i)->setControl(periph);
   }
 for (size_t i = _player->getPlayerCount() - _player->getIACount(); i < _player->getPlayerCount() ; i++)
   _player->getPlayer(i)->setControl(_iACenter->addNewIA((_player->getPlayer(i))));
 _iAThread = new CThread::Thread(_iACenter);
}

void		GameParty::initialize(Info const& info)
{
  if (_player || _board)
    reinit();
  if (info.getSaveFile() != "")
    {
      SaveLoad load(this);
      load.loadParty(info.getSaveFile());
    }
  else
    {
      MapLoader	loader(*this, info);

      _player = new GamePlayer(info.getNPlayers() + info.getNAi(), info.getNAi());
      _player->getIACount() = info.getNAi();
      _board = loader.loadMap();
    }
  _alive = 0;
  _board->flush();
  start();
}

int GameParty::update(gdl::Clock const &clock, gdl::Input &input)
{
  unsigned int		i;

  i = 0;
  _alive = 0;
  while (i < (_player->getPlayerCount()))
    {
      Controller::IControl	*control;
      if (i < _player->getUserCount() &&
	  (control = _player->getPlayer(i)->getControl()))
	{
	  control->checkMove(input);
	  Controller::Button but = control->getBut();
	  if (but == Controller::BUTTON_START)
	    {
	      _pause->initialize(_player->getPlayer(i)->getControl(), this, i);
	      return (2);
	    }
	  if (_saveDelay <= 0 &&
	      but == Controller::BUTTON_BACK)
	    {
	      SaveLoad save(this);

	      save.saveParty();
	      _saveDelay = 5;
	    }
	  if (but == Controller::BUTTON_LEFTSHOULDER &&
	      _cameras[i]->getCameraDiff().z > 0.3f)
	    {
	      _cameras[i]->getCameraDiff().z -= clock.getElapsed() * 5.0f;
	    }
	  if (but == Controller::BUTTON_RIGHTSHOULDER &&
	      _cameras[i]->getCameraDiff().z < 10.0f)
	    {
	      _cameras[i]->getCameraDiff().z += clock.getElapsed() * 5.0f;
	    }
	}
      _alive += (_player->getPlayer(i)->getPerson() != NULL);
      ++i;
    }
  _saveDelay -= (_saveDelay > 0) * clock.getElapsed();
  if (_board)
    _board->update(clock, input);

  if ((_alive <= 1 && _alive < _player->getPlayerCount()) || (_alive == 0))
    _waiting -= clock.getElapsed();
  if (_waiting <= 0 && _alive <= 1)
    {
      _iACenter->stop();
      return (0);
    }
  return (1);
}

void	GameParty::stopIA()
{
  if (_iACenter)
    _iACenter->stop();
  _iACenter = NULL;
}

void	GameParty::reinit()
{
  _cameras.clear();
  if (_iAThread)
    {
      delete _iAThread;
      _iAThread = NULL;
    }
  _iACenter = NULL;
  if (_board)
    {
      delete _board;
      _board = NULL;
    }
  if (_player)
    {
      delete _player;
      _player = NULL;
    }
  _cameras.clear();
}

# include <math.h>

void	GameParty::intelligentSplit(Screen::AScreen &screen)
{
  int	scrCount = _player->getUserCount();
  int	dimx = ceil(sqrt(scrCount));
  int	dimy = ceil(static_cast<float>(scrCount) / static_cast<float>(dimx));
  int	i(0);

  while (i < scrCount)
    {
      Screen::ACamera		*cam = new Screen::AutoCamera(_player->getPlayer(i));
      Screen::ASubScreen	*a = new Screen::ASubScreen
	(cam);
      cam->getCameraDiff().z = 5.0f;
      a->getSize().x /= dimx;
      a->getSize().y /= dimy;
      a->getPos().x = (i % dimx) * a->getSize().x;
      a->getPos().y = (i / dimx) * a->getSize().y;
      _cameras.push_back(cam);
      screen.addScreen(a);
      ++i;
    }
}

void	GameParty::initScreen(Screen::AScreen &screen)
{
  screen.cleanScreens();
  _cameras.clear();
  intelligentSplit(screen);
}

void GameParty::drawScore(Screen::AScreen &screen,
			  gdl::Clock const&)
{
  unsigned int	i = 0;

  while (i < _player->getUserCount())
    {
      std::ostringstream	os;
      glm::vec2 const& size((screen.getScreens()[i])->getSize());

      os << "score " << _player->getPlayer(i)->getScore();
      DrawComponent::putsSubScreen(os.str(), glm::vec2(0, size.y / 11 * 5), screen,
				   *(screen.getScreens()[i]), glm::vec3(0.2, 1, 0.5));
      ++i;
    }
}

void GameParty::draw(Screen::AScreen &screen, gdl::Clock const &clock)
{
  std::vector<Screen::ASubScreen *>	sc;
  unsigned 				i = 0;

  sc = screen.getScreens();
  if (_board)
    {
      glEnable(GL_SCISSOR_TEST);

      (screen).update();

      while (i < sc.size())
	{
	  sc[i]->apply(screen.getShader());
	  glm::vec3	vec1(sc[i]->getCamera()->getLookAt());
	  DrawComponent	const*	_toDraw = DrawComponent::getComponent("Ground");
	  glm::mat4		transform(1);

	  glActiveTexture(GL_TEXTURE0);
	  _toDraw->getTexture().bind();
	  transform = glm::translate(transform, glm::vec3(vec1.x, -0.1, vec1.z));
	  _toDraw->getGeometry()->draw(screen.getShader(), transform, GL_QUADS);
	  ++i;
	}

      _board->draw(screen, clock);

      i = 0;
      while (i < _player->getPlayerCount() - _player->getIACount())
	{
	  if (!_player->getPlayer(i)->getPerson())
	    DrawComponent::putsSubScreen("dead", glm::vec2(0, 0), screen,
					 *(screen.getScreens()[i]), glm::vec3(1, 1, 1));
	  else if (_alive == 1 && _waiting < victory_time)
	    DrawComponent::putsSubScreen("win", glm::vec2(0, 0), screen,
					 *(screen.getScreens()[i]), glm::vec3(1, 1, 1));
	  ++i;
	}
      glDisable(GL_SCISSOR_TEST);
      drawScore(screen, clock);
    }
}

int	GameParty::getPlayerIdx(Player const *pl) const
{
  unsigned int	i;

  i = 0;
  while (i < _player->getPlayerCount())
    {
      if (pl == _player->getPlayer(i))
	return (i);
      ++i;
    }
  return (0);
}

void	GameParty::saveSelf(std::ostream &ofs)
{
  ofs << "<GamePlayer" << std::endl;
  if (!_player)
    throw BombermanException("Cant save without initialize!");
  _player->saveSelf(ofs);
  ofs << "GamePlayer> <Board" << std::endl;
  _board->saveSelf(ofs);
  ofs << "Board>" << std::endl;
}

GameParty::~GameParty()
{
  if (_iAThread)
    delete _iAThread;
  if (_board)
    delete _board;
  if (_player)
    delete _player;
}
