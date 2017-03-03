#include "Menus.hh"
#include "EntityFactory.hh"
#include "Clock.hh"
#include "Position.hh"
#include "Entity.hpp"
#include <unistd.h>
#include <iostream>
#include <GL/glew.h>
#include "MapEditor.hpp"
#include "AFullScreen.hpp"
#include "MasterController.hpp"

static std::vector<Entity*>		initbackground()
{
  std::vector<Entity*>			_background(5);

  _background[0] = new Entity;
  _background[1] = new Entity;
  _background[2] = new Entity;
  _background[3] = new Entity;
  _background[4] = new Entity;
  _background[0]->addComponent(new Position(NULL));
  _background[1]->addComponent(new Position(NULL));
  _background[2]->addComponent(new Position(NULL));
  _background[3]->addComponent(new Position(NULL));
  _background[4]->addComponent(new Position(NULL, glm::vec3(0.0,0.1,0.0)));
  _background[0]->addComponent(new GeometryDraw("MenuStart1"));
  _background[1]->addComponent(new GeometryDraw("MenuStart2"));
  _background[2]->addComponent(new GeometryDraw("MenuVirgin"));
  _background[3]->addComponent(new GeometryDraw("MenuBomb"));
  _background[4]->addComponent(new GeometryDraw("MenuCredits"));
  return ((_background));
}

std::vector<Entity*> Menus::_background;

/*
** ctor && dtor
*/
Menus::Menus(Info& info, GameParty* game, Zik& sound, MapEditor *editor)
  : _move(Controller::MasterController::rtPeripheral()),
    _info(info), _play(game), _sound(sound)
{
  _editor = editor;
  _fnctMenuStack.push(&Menus::menuStart);
  _drawStack.push(&Menus::drawMain);
  Scoring::initialize(10);
  _ptr[0][0] = &Menus::MenuPlay;
  _ptr[0][1] = &Menus::Map;
  _ptr[0][2] = &Menus::Player;
  _ptr[0][3] = &Menus::MenuStart;
  _ptr[1][0] = &Menus::MenuMod;
  _ptr[1][1] = &Menus::MenuModBomb;
  _ptr[1][2] = &Menus::MenuModWall;
  _ptr[1][3] = &Menus::MenuModTP;
  _ptr[2][0] = &Menus::MenuLoad;
  _ptr[3][0] = &Menus::MenuEdit;
  _ptr[3][3] = &Menus::MenuStartEdit;
  _ptr[4][0] = &Menus::MenuScore;
  _ptr[5][0] = &Menus::MenuOption;
  _ptr[6][0] = &Menus::MenuCredit;
  _ptr[7][0] = &Menus::MenuExit;
  _tabdrawptr[0][0] = &Menus::drawPlay;
  _tabdrawptr[0][1] = &Menus::drawMap;
  _tabdrawptr[0][2] = &Menus::drawPlayer;
  _tabdrawptr[0][3] = &Menus::drawMain;
  _tabdrawptr[1][0] = &Menus::drawMod;
  _tabdrawptr[2][0] = &Menus::drawLoad;
  _tabdrawptr[3][0] = &Menus::drawEditor;
  _tabdrawptr[4][0] = &Menus::drawScore;
  _tabdrawptr[5][0] = &Menus::drawMain;
  _tabdrawptr[6][0] = &Menus::drawCredits;
  _background = initbackground();
  _val = 0;
  _timeaff = 0.0f;
  _index = 0;
  _sound.zPlay(Zik::MENU, true);
  _dirread.openFolder(PATH_SAVEDIR);
  _dirread.setExtension("save");
  _tabstr.push_back("mapx");
  _tabstr.push_back("mapy");
  _tabstr.push_back("free");
  _tabstr.push_back("unde");
  _tabstr.push_back("maze");
  _tabstr.push_back("nplayer");
  _tabstr.push_back("nai");
}

Menus::~Menus()
{
}

int Menus::initialize(gdl::Input&, gdl::Clock const &)
{
  _info.getMod() = Info::NONE;
  _dirread.setExtension("save");
  _val = 0;
  _fnctMenuStack.pop();
  _sound.zPlay(Zik::MENU, true);
  return (0);
}

void Menus::initScreen(Screen::AScreen& scr)
{
  Screen::ACamera *cam = new Screen::ACamera;

  scr.cleanScreens();
  cam->getLookAt() = glm::vec3(0, 10, 0.0);

  scr.addScreen(new Screen::AFullScreen(cam));
}

int		Menus::menuStart(gdl::Input& input, gdl::Clock const &)
{
  _move->checkMove(input);
  if (_move->getBut() != Controller::BUTTON_START)
    {
      _timewait = 0.05f;
      return (0);
    }
  _fnctMenuStack.push(&Menus::menuMain);
  _timewait = TIMEMENU;
  return (0);
}

bool	Menus::TranslatedSprite(Entity* gr, glm::vec3& vec,
				gdl::Clock const& cl, Screen::AScreen& scr)
{
  GeometryDraw	*todraw;

  if ((todraw = gr->getComponent<GeometryDraw>()))
    {
      Position* pos;
      if ((pos = gr->getComponent<Position>()))
	pos->getPos() = vec;
      todraw->draw(scr, cl);
    }
  return (true);
}

bool	Menus::MenusChoose(int tabsize, int& val, Controller::Peripheral* move, Zik& sound)
{
  if (move->getDir().getSpeed() > 0 && ABS(move->getDir().getAngle()) > 45.0f)
    {
      sound.zPlay(Zik::SMOVESELECT);
      val--;
    }
  else if (move->getDir().getSpeed() > 0 && ABS(move->getDir().getAngle()) < 45.0f)
    {
      sound.zPlay(Zik::SMOVESELECT);
      val++;
    }
  if (val < 0)
    val = tabsize - 1;
  else if (val >= tabsize)
    val = 0;
  return (true);
}

int	Menus::menuMain(gdl::Input& input, gdl::Clock const &cl)
{
  Controller::Button	but;

  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB && but != Controller::BUTTON_START)
    {
      MenusChoose(8, _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  _timewait = TIMEMENU;
  _sound.zPlay(Zik::SSELECTION);
  _fnctMenuStack.push(_ptr[_val][0]);
  if (static_cast<unsigned int>(_val) < sizeof(_tabdrawptr) / sizeof(_tabdrawptr[0]))
    _drawStack.push(_tabdrawptr[_val][0]);
  _val = 0;
  return (0);
}

int		Menus::MenuPlay(gdl::Input &input, gdl::Clock const &cl)
{
  Controller::Button	but;

  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_MODE
      && but != Controller::BUTTON_START)
    {
      MenusChoose(3, _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  _timewait = TIMEMENU;
  _sound.zPlay(Zik::SSELECTION);
  if (but == Controller::BUTTON_START)
    {
      if (_val != 2)
	_val = 2;
      else
	{
	  _fnctMenuStack.push(&Menus::MenuStart);
	}
      return (0);
    }
  if (but == Controller::BUTTON_MODE)
    {
      _fnctMenuStack.pop();
      _drawStack.pop();
      _sound.zPlay(Zik::CMDRETURN);
    }
  else
    {
      _drawStack.push(_tabdrawptr[0][_val + 1]);
      _fnctMenuStack.push(_ptr[0][_val + 1]);
    }
  return (0);
}

int	Menus::Map(gdl::Input &input, gdl::Clock const& cl)
{
  Controller::Button	but;

  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_MODE
      && but != Controller::BUTTON_START)
    {
      MenusChoose(5, _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  _timewait = TIMEMENU;
  _sound.zPlay(Zik::SSELECTION);
  if (but == Controller::BUTTON_MODE)
    {
      _fnctMenuStack.pop();
      _drawStack.pop();
      _sound.zPlay(Zik::CMDRETURN);
    }
  else
    {
      _fnctMenuStack.push(&Menus::changeVal);
    }
  return (0);
}

int	Menus::Player(gdl::Input &input, gdl::Clock const& cl)
{
  Controller::Button	but;

  if (_val > 1)
    _val = 0;
  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_MODE
      && but != Controller::BUTTON_START)
    {
      MenusChoose(2, _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  _timewait = TIMEMENU;
  _sound.zPlay(Zik::SSELECTION);
  if (but == Controller::BUTTON_MODE)
    {
      _fnctMenuStack.pop();
      _drawStack.pop();
      _sound.zPlay(Zik::CMDRETURN);
    }
  else
    {
      _val += 5;
      _fnctMenuStack.push(&Menus::changeVal);
    }
  return (0);
}

int	Menus::changeVal(gdl::Input &input, gdl::Clock const& cl)
{
  int	inter[][2] =
    {
      {
	10,
	10,
      },
      {
	10,
	10,
      },
      {
	0,
	100,
      },
      {
	0,
	100,
      },
      {
	0,
	1,
      },
      {
	1,
	Controller::MasterController::getNController(),
      },
      {
	0,
	0,
      },
    };
  return (AddVal(input, cl, _tabstr[_val], inter[_val][0], inter[_val][1]));
}

typedef size_t&	(Info::*infoptr)();

int	Menus::AddVal(gdl::Input &input, gdl::Clock const &cl, std::string str, size_t min, size_t max)
{
  Controller::Button			but;
  static float				speedModif = 1;
  std::map<std::string, infoptr>	infomap;

  infomap["mapx"] = &Info::getMapX;
  infomap["mapy"] = &Info::getMapY;
  infomap["nplayer"] = &Info::getNPlayers;
  infomap["nai"] = &Info::getNAi;
  infomap["free"] = &Info::getFreeBlock;
  infomap["unde"] = &Info::getUndeBlock;
  infomap["maze"] = &Info::getPerfectMaze;

  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_START
      && but != Controller::BUTTON_MODE)
    {
      if (_move->getDir().getSpeed() > 0 && ABS(_move->getDir().getAngle()) > 135.0f)
	{
	  _sound.zPlay(Zik::SCHANGEVAL);
	  if (max == min || ((_info.*infomap[str])() + (1 * speedModif)) < max)
	    (_info.*infomap[str])() += (1 * speedModif);
	  else
	    (_info.*infomap[str])() = max;
	  speedModif *= 1.02;
	}
      else if (_move->getDir().getSpeed() > 0 && ABS(_move->getDir().getAngle()) < 45.0f)
	{
	  _sound.zPlay(Zik::SCHANGEVAL);
	  if (((_info.*infomap[str])() - (1 * speedModif)) > min)
	    (_info.*infomap[str])() -= (1 * speedModif);
	  else
	    (_info.*infomap[str])() = min;
	  speedModif *= 1.02;
	}
      else
	speedModif = 1.0f;
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  else
    _fnctMenuStack.pop();
  _timewait = TIMEMENU;
  return (0);
}

int	Menus::CheckScore(int& maxScore)
{
  GamePlayer* gp = _play->getGamePlayer();
  for (unsigned int i = 0 ; i < gp->getUserCount() ; i++)
    {
      if (maxScore < gp->getPlayer(i)->getScore())
	maxScore = gp->getPlayer(i)->getScore();
    }
  return (0);
}

int	Menus::getPlayerName(gdl::Input &)
{
  SDL_Event event;

  SDL_WaitEvent(&event);
  if (event.type == SDL_KEYDOWN)
    {
      std::string str = SDL_GetKeyName(event.key.keysym.sym);

      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      if (str == "return")
	return (1);
      if (str == "backspace")
	{
	  std::string str2 = _pName.str();
	  str2.erase(str2.end() - 1, str2.end());
	  _pName.str(std::string());
	  _pName << str2;
	}
      else if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= '0' && str[0] <= '9'))
	_pName << str[0];
    }
  return (0);
}

int	Menus::Replay(gdl::Input &input, gdl::Clock const& cl)
{
  static int		maxScore = -1000000000;
  static int		where = 0;
  static int		pos = 0;
  Controller::Button	but;

  if (where == 0)
    {
      _sound.zStop(Zik::INGAME);
      _sound.zPlay(Zik::MENU, true);
      CheckScore(maxScore);
      if (!(pos = Scoring::isInLadder(maxScore)))
	where++;
      else
	_drawStack.push(&Menus::drawScorePlayer);
      where++;
      return (0);
    }
  else if (where == 1)
    {
      if (getPlayerName(input) == 1)
	{
	  Scoring::addScore(pos, _pName.str(), maxScore);
	  where++;
	  _drawStack.pop();
	}
      return (0);
    }
  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_START)
    {
      MenusChoose(2, _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  if (_play->getBoard())
    _play->reinit();
  where = 0;
  _pName.str(std::string());
  maxScore = 0;
  _drawStack.pop();
  if (_val == 0)
    {
      _fnctMenuStack.push(&Menus::MenuStart);
      return (0);
    }
  _info.getSaveFile() = std::string();
  _fnctMenuStack.pop();
  _timewait = TIMEMENU;
  return (0);
}

int	Menus::MenuStart(gdl::Input &, gdl::Clock const &)
{
  _sound.zPlay(Zik::GAMESTART);

  while (!_fnctMenuStack.empty())
    _fnctMenuStack.pop();
  _fnctMenuStack.push(&Menus::menuStart);
  _fnctMenuStack.push(&Menus::menuMain);
  _fnctMenuStack.push(&Menus::initialize);
  while (!_drawStack.empty())
    _drawStack.pop();
  _drawStack.push(&Menus::drawMain);
  _val = 0;
  Controller::MasterController::restart();
  _info.getRealFree() = ABS(static_cast<int>(_info.getFreeBlock() - 100));
  _info.getRealUnde() = _info.getUndeBlock();
  try {
    _sound.zPlay(Zik::INGAME, true);
    _play->initialize(_info);
  }
  catch (std::exception &e)
    {
      _sound.zStop(Zik::INGAME);
      _drawStack.push(&Menus::drawErrorMapGen);
      _fnctMenuStack.push(&Menus::MenuCredit);
      return (0);
    }
  _fnctMenuStack.push(&Menus::Replay);
  _drawStack.push(&Menus::drawReplay);
  _sound.zStop(Zik::MENU);
  return (1);
}

int	Menus::MenuMod(gdl::Input &input, gdl::Clock const &cl)
{
  Controller::Button	but;

  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB
	 && but != Controller::BUTTON_START
	 && but != Controller::BUTTON_MODE)
    {
      MenusChoose(static_cast<int>(Info::WALL), _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  _timewait = TIMEMENU;
  _sound.zPlay(Zik::SSELECTION);
  if (but == Controller::BUTTON_MODE)
    {
      _fnctMenuStack.pop();
      _sound.zPlay(Zik::CMDRETURN);
      _drawStack.pop();
    }
  else
    {
      _drawStack.push(&Menus::drawPlay);
      _fnctMenuStack.push(_ptr[1][_val + 1]);
    }
  return (0);
}

int	Menus::MenuModWall(gdl::Input &, gdl::Clock const &)
{
  _sound.zPlay(Zik::SSELECTION);
  _info.getMod() = Info::WALL;
  _val = 0;
  _fnctMenuStack.pop();
  _fnctMenuStack.push(&Menus::MenuPlay);
  return (0);
}

int	Menus::MenuModBomb(gdl::Input &, gdl::Clock const &)
{
  _sound.zPlay(Zik::SSELECTION);
  _info.getMod() = Info::MOVEBOMB;
  _val = 0;
  _fnctMenuStack.pop();
  _fnctMenuStack.push(&Menus::MenuPlay);
  return (0);
}

int	Menus::MenuModTP(gdl::Input &, gdl::Clock const &)
{
  _sound.zPlay(Zik::SSELECTION);
  _info.getMod() = Info::TELEPORT;
  _val = 0;
  _fnctMenuStack.pop();
  _fnctMenuStack.push(&Menus::MenuPlay);
  return (0);
}

int	Menus::MenuLoad(gdl::Input& input, gdl::Clock const& cl)
{
  Controller::Button	but;

  _dirread.setExtension("save");
  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_START
      && but != Controller::BUTTON_MODE && _dirread.getFileList().size() > 0)
    {
      MenusChoose(_dirread.getFileList().size(), _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  if (but == Controller::BUTTON_MODE)
    {
      _timewait = TIMEMENU;
      _fnctMenuStack.pop();
      _sound.zPlay(Zik::CMDRETURN);
      _drawStack.pop();
    }
  else if (_dirread.getFileList().size() > 0)
    {
      _info.getSaveFile() = ".saves/" +  _dirread.getFileList()[_val];
      _fnctMenuStack.push(&Menus::MenuStart);
    }
  else
    {
      _drawStack.push(&Menus::drawLoadNone);
      return (0);
    }
  return (0);
}

int	Menus::MenuEdit(gdl::Input& input, gdl::Clock const& cl)
{
  Controller::Button	but;

  _move->checkMove(input);
  but = _move->getBut();
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  if (but == Controller::BUTTON_START)
    {
      _val = 2;
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  if (but != Controller::BUTTON_PUTBOMB
	 && but != Controller::BUTTON_START
	 && but != Controller::BUTTON_MODE)
    {
      MenusChoose(2, _val, _move, _sound);
      _timewait = TIMEMENUCHOOSE;
      return (0);
    }
  _timewait = TIMEMENU;
  _sound.zPlay(Zik::SSELECTION);
  if (but == Controller::BUTTON_MODE)
    {
      _fnctMenuStack.pop();
      _sound.zPlay(Zik::CMDRETURN);
      _drawStack.pop();
    }
  else
    {
      if (_val == 0)
	_drawStack.push(&Menus::drawMap);
      _fnctMenuStack.push((_val == 0 ? &Menus::Map : &Menus::MenuStartEdit));
    }
  return (0);
}

int	Menus::MenuStartEdit(gdl::Input &, gdl::Clock const &)
{
  _sound.zPlay(Zik::GAMESTART);
  while (!_fnctMenuStack.empty())
    _fnctMenuStack.pop();
  _fnctMenuStack.push(&Menus::menuStart);
  _fnctMenuStack.push(&Menus::menuMain);
  _fnctMenuStack.push(&Menus::initialize);
  while (!_drawStack.empty())
    _drawStack.pop();
  _drawStack.push(&Menus::drawMain);
  _val = 0;
  _editor->initialize(_info);
  _sound.zStop(Zik::MENU);
  return (3);
}

int	Menus::MenuScore(gdl::Input &input, gdl::Clock const &cl)
{
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  _move->checkMove(input);
  if (_move->getBut() == Controller::BUTTON_PUTBOMB
      || _move->getBut() == Controller::BUTTON_START)
    {
      _timewait = TIMEMENU;
      _sound.zPlay(Zik::CMDRETURN);
      _fnctMenuStack.pop();
      _drawStack.pop();
    }
  return (0);
}

int	Menus::MenuOption(gdl::Input &input, gdl::Clock const &)
{
  (void)input;
  _fnctMenuStack.pop();
  return (0);
}

int	Menus::MenuCredit(gdl::Input &input, gdl::Clock const &cl)
{
  (void)input;
  timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (0);
  _move->checkMove(input);
  if (_move->getBut() == Controller::BUTTON_PUTBOMB
      || _move->getBut() == Controller::BUTTON_START)
    {
      _drawStack.pop();
      _timewait = TIMEMENU;
      _sound.zPlay(Zik::CMDRETURN);
      _fnctMenuStack.pop();
    }
  return (0);
}

int	Menus::MenuExit(gdl::Input &, gdl::Clock const &)
{
  return (-1);
}

bool	Menus::timeWaiting(float& timewait, gdl::Clock const& cl)
{
  timewait -= cl.getElapsed();
  if (timewait <= 0.0f)
    {
      timewait = 0.0f;
      return (true);
    }
  return (false);
}

int	Menus::update(gdl::Clock const &cl, gdl::Input &input)
{
  ptrMenu ptr = _fnctMenuStack.top();

  return ((this->*ptr)(input, cl));
}

void	Menus::drawCredits(Screen::AScreen& scr, gdl::Clock const& cl)
{
  _background[4]->draw(scr, cl);
}

void	Menus::draw(Screen::AScreen& scr, gdl::Clock const& cl)
{
  GeometryDraw *todraw;

  if (_fnctMenuStack.size() == 1)
    {
      if ((todraw = _background[_index]->getComponent<GeometryDraw>()))
	todraw->draw(scr, cl);
      if (timeWaiting(_timeaff, cl))
	{
	  _timeaff = 0.2f;
	  ++_index %= 2;
	}
    }
  else
    {
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0.0f);
      _background[2]->draw(scr, cl);
      drawPtr drawptr = _drawStack.top();
      if (drawptr)
	(this->*drawptr)(scr, cl);
      glDisable(GL_ALPHA_TEST);
    }
}

void	Menus::drawMain(Screen::AScreen& scr, gdl::Clock const& cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-18.0f, 0.1f, -7.0f),
	glm::vec3(-9.0f, 0.1f, -7.0f),
      },
      {
	glm::vec3(-18.0f, 0.1f, -4.5f),
	glm::vec3(-11.0f, 0.1f, -4.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, -2.0f),
	glm::vec3(-10.0f, 0.1f, -2.0f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 0.5f),
	glm::vec3(-10.0f, 0.1f, 0.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 2.3f),
	glm::vec3(-9.5f, 0.1f, 2.3f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 6.0f),
	glm::vec3(-8.0f, 0.1f, 6.0f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 8.4f),
	glm::vec3(-8.0f, 0.1f, 8.4f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 11.0f),
	glm::vec3(-11.0f, 0.1f, 11.0f),
      },
    };
  DrawComponent::putstring("start", glm::vec3(-16.5f, 0.1f, -7.5f), scr, cl);
  DrawComponent::putstring("mod", glm::vec3(-16.5f, 0.1f, -5.0f), scr, cl);
  DrawComponent::putstring("load", glm::vec3(-16.5f, 0.1f, -2.5f), scr, cl);
  DrawComponent::putstring("edit", glm::vec3(-16.5f, 0.1f, 0.0f), scr, cl);
  DrawComponent::putstring("score", glm::vec3(-16.5f, 0.1f, 2.8f), scr, cl);
  DrawComponent::putstring("option", glm::vec3(-16.5f, 0.1f, 5.5f), scr, cl);
  DrawComponent::putstring("credit", glm::vec3(-16.5f, 0.1f, 8.1f), scr, cl);
  DrawComponent::putstring("exit", glm::vec3(-16.5f, 0.1f, 10.5f), scr, cl);
  TranslatedSprite(_background[3], tabvec[_val][0], cl, scr);
  TranslatedSprite(_background[3], tabvec[_val][1], cl, scr);
}

void	Menus::drawEditor(Screen::AScreen& scr, gdl::Clock const& cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-18.0f, 0.1f, -4.5f),
	glm::vec3(-18.0f, 0.1f, -4.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, -1.9f),
	glm::vec3(-9.0f, 0.1f, -1.9f),
      },
    };

  DrawComponent::putstring("map", glm::vec3(-16.5f, 0.1f, -5.0f), scr, cl);
  DrawComponent::putstring("start", glm::vec3(-16.5f, 0.1f, -2.5f), scr, cl);
  TranslatedSprite(_background[3], tabvec[_val][0], cl, scr);
  TranslatedSprite(_background[3], tabvec[_val][1], cl, scr);
}

void	Menus::drawMod(Screen::AScreen& scr, gdl::Clock const& cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-18.0f, 0.1f, -4.5f),
	glm::vec3(-5.0f, 0.1f, -4.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, -2.1f),
	glm::vec3(-10.0f, 0.1f, -2.1f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 0.4f),
	glm::vec3(-5.0f, 0.1f, 0.4f),
      },
    };

  DrawComponent::putstring("movebomb", glm::vec3(-16.5f, 0.1f, -5.0f), scr, cl);
  DrawComponent::putstring("wall", glm::vec3(-16.5f, 0.1f, -2.5f), scr, cl);
  DrawComponent::putstring("teleport", glm::vec3(-16.5f, 0.1f, 0.0f), scr, cl);
  TranslatedSprite(_background[3], tabvec[_val][0], cl, scr);
  TranslatedSprite(_background[3], tabvec[_val][1], cl, scr);
}

void	Menus::drawPlay(Screen::AScreen& scr, gdl::Clock const& cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-18.0f, 0.1f, -4.5f),
	glm::vec3(-18.0f, 0.1f, -4.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, -2.1f),
	glm::vec3(-18.0f, 0.1f, -2.1f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 0.5f),
	glm::vec3(-9.0f, 0.1f, 0.5f),
      },
    };
  DrawComponent::putstring("map", glm::vec3(-16.5f, 0.1f, -5.0f), scr, cl);
  DrawComponent::putstring("player", glm::vec3(-16.5f, 0.1f, -2.5f), scr, cl);
  DrawComponent::putstring("start", glm::vec3(-16.5f, 0.1f, 0.f), scr, cl);
  TranslatedSprite(_background[3], tabvec[_val][0], cl, scr);
  TranslatedSprite(_background[3], tabvec[_val][1], cl, scr);
}

void	Menus::drawMap(Screen::AScreen& scr, gdl::Clock const& cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-18.0f, 0.1f, -4.5f),
	glm::vec3(-18.0f, 0.1f, -4.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, -2.1f),
	glm::vec3(-18.0f, 0.1f, -2.1f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 0.5f),
	glm::vec3(-18.0f, 0.1f, 0.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 2.9f),
	glm::vec3(-18.0f, 0.1f, 2.9f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 5.4f),
	glm::vec3(-18.0f, 0.1f, 5.4f),
      },
    };
  DrawComponent::putstring("mapx", glm::vec3(-16.5f, 0.1f, -5.0f), scr, cl);
  DrawComponent::putstring("mapy", glm::vec3(-16.5f, 0.1f, -2.5f), scr, cl);
  DrawComponent::putstring("block", glm::vec3(-16.5f, 0.1f, 0.0f), scr, cl);
  DrawComponent::putstring("unde", glm::vec3(-16.5f, 0.1f, 2.5f), scr, cl);
  DrawComponent::putstring("maze", glm::vec3(-16.5f, 0.1f, 5.0f), scr, cl);
  TranslatedSprite(_background[3], tabvec[_val][0], cl, scr);
  TranslatedSprite(_background[3], tabvec[_val][1], cl, scr);

  std::ostringstream str;
  size_t (Info::*infoPtr[])() const =
    {
      &Info::getMapX,
      &Info::getMapY,
      &Info::getFreeBlock,
      &Info::getUndeBlock,
    };
  for (size_t i = 0 ; i <= 3 ; i++)
    {
      str << (_info.*infoPtr[i])();
      tabvec[i][0].x = -8.0f;
      tabvec[i][0].z -= 0.5f;
      DrawComponent::putstring(str.str(), tabvec[i][0], scr, cl);
      str.str(std::string());
      tabvec[i][0].x = -18.0f;
      tabvec[i][0].z += 0.5f;
    }
  tabvec[4][0].x = -8.0f;
  tabvec[4][0].z -= 0.5f;
  DrawComponent::putstring((_info.getPerfectMaze() == 0 ?
			    "true" : "false"), tabvec[4][0], scr, cl);
  tabvec[4][0].x = -18.0f;
  tabvec[4][0].z += 0.5f;
}

void	Menus::drawPlayer(Screen::AScreen& scr, gdl::Clock const& cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-18.0f, 0.1f, -4.5f),
	glm::vec3(-18.0f, 0.1f, -4.5f),
      },
      {
	glm::vec3(-18.0f, 0.1f, -2.1f),
	glm::vec3(-18.0f, 0.1f, -2.1f),
      },
    };
  DrawComponent::putstring("player", glm::vec3(-16.5f, 0.1f, -5.0f), scr, cl);
  DrawComponent::putstring("ai", glm::vec3(-16.5f, 0.1f, -2.5f), scr, cl);
  TranslatedSprite(_background[3], tabvec[_val][0], cl, scr);
  TranslatedSprite(_background[3], tabvec[_val][1], cl, scr);

  std::ostringstream str;
  size_t (Info::*infoPtr[])() const =
    {
      &Info::getNPlayers,
      &Info::getNAi
    };
  for (size_t i = 0 ; i <= 1 ; i++)
    {
      str << (_info.*infoPtr[i])();
      tabvec[i][0].x = -8.0f;
      tabvec[i][0].z -= 0.5f;
      DrawComponent::putstring(str.str(), tabvec[i][0], scr, cl);
      str.str(std::string());
      tabvec[i][0].x = -18.0f;
      tabvec[i][0].z += 0.5f;
    }
}

void		Menus::drawLoad(Screen::AScreen& scr, gdl::Clock const& cl)
{
  glm::vec3 tabvec = glm::vec3(-16.5f, 0.1f, -5.0f);
  std::string str;
  std::vector<std::string> lfile = _dirread.getFileList();

  int val = 0;
  for (std::vector<std::string>::iterator it = (_val < 6 ? lfile.begin() : lfile.begin() + (_val - 5)) ; it < lfile.end() && val < 6 ; it++)
    {
      str = *it;
      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      size_t i = str.find(".save");
      str.erase(i, str.size() - i);
      std::replace(str.begin(), str.end(), '_', ' ');
      DrawComponent::putstring(str, tabvec, scr, cl);
      tabvec.z += 2.5f;
      val++;
    }
  tabvec.x = -18.0f;
  tabvec.z = -4.5f;
  tabvec.z += 2.5 * (_val < 6 ? _val : 5);
  TranslatedSprite(_background[3], tabvec, cl, scr);
}

void		Menus::drawLoadNone(Screen::AScreen& scr, gdl::Clock const& cl)
{
  glm::vec3 tabvec = glm::vec3(-16.5f, 0.1f, -5.0f);

  DrawComponent::putstring("no save", tabvec, scr, cl);
}

void		Menus::drawErrorMapGen(Screen::AScreen& scr, gdl::Clock const& cl)
{
  glm::vec3 tabvec = glm::vec3(-16.5f, 0.1f, -5.0f);

  DrawComponent::putstring("too many players on the map", tabvec, scr, cl);
}

void		Menus::drawReplay(Screen::AScreen& scr, gdl::Clock const& cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-18.0f, 0.1f, 8.4f),
	glm::vec3(-7.0f, 0.1f, 8.4f),
      },
      {
	glm::vec3(-18.0f, 0.1f, 11.0f),
	glm::vec3(-10.0f, 0.1f, 11.0f),
      },
    };
  glm::vec3	vec = glm::vec3(-16.5f, 0.1, -5.0f);

  GamePlayer* gp = _play->getGamePlayer();
  for (unsigned int i = 0 ; i < gp->getUserCount() ; i++)
    {
      std::ostringstream str;
      str << "player" << i << "  " << gp->getPlayer(i)->getScore();
      DrawComponent::putstring(str.str(), vec, scr, cl);
      vec.z += 2.5f;
    }
  DrawComponent::putstring("restart", glm::vec3(-16.5f, 0.1f, 8.1f), scr, cl);
  DrawComponent::putstring("menu", glm::vec3(-16.5f, 0.1f, 10.5f), scr, cl);
  TranslatedSprite(_background[3], tabvec[_val][0], cl, scr);
  TranslatedSprite(_background[3], tabvec[_val][1], cl, scr);
}

void		Menus::drawScorePlayer(Screen::AScreen& scr, gdl::Clock const& cl)
{
  drawReplay(scr, cl);
  DrawComponent::putstring(_pName.str(), glm::vec3(-16.5f, 0.1, -7.0f), scr, cl);
}

void		Menus::drawScore(Screen::AScreen& scr, gdl::Clock const& cl)
{
  std::string	name;
  int		val;

  glm::vec3	vec = glm::vec3(-16.5f, 0.1, -10.0f);

  for (unsigned int i = 1 ; i < 11 ; i++)
    {
      std::ostringstream str;
      str << "best_player_" << i;
      ConfigLoader::getVarValue("Score", str.str(), name);
      std::transform(name.begin(), name.end(), name.begin(), ::tolower);
      DrawComponent::putstring(name, vec, scr, cl);
      vec.x = 5.0f;
      str.str(std::string());
      str << "best_score_" << i;
      ConfigLoader::getVarValue("Score", str.str(), val);
      str.str(std::string());
      str << val;
      DrawComponent::putstring(str.str(), vec, scr, cl);
      vec.x = -16.5f;
      vec.z += 2.0f;
    }
}
