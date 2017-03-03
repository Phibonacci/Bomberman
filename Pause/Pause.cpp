#include "Pause.hpp"
#include "Menus.hh"
#include "GameParty.hh"
#include <iostream>

Pause::Pause(Zik& sound)
 : _sound(sound)
{
  _val = 0;
  _pausePtr.push(&Pause::WaitInPause);
  _ptrfnct[0][0] = &Pause::returnToGame;
  _ptrfnct[1][0] = &Pause::Commands;
  _ptrfnct[1][1] = &Pause::CommandsBomb;
  _ptrfnct[1][2] = &Pause::CommandsMode;
  _ptrfnct[1][3] = &Pause::CommandsStart;
  _ptrfnct[1][4] = &Pause::CommandsUpCam;
  _ptrfnct[1][5] = &Pause::CommandsDownCam;
  _ptrfnct[2][0] = &Pause::backToMenu;
  _drawfnct = &Pause::drawPause;
}

void Pause::initialize(Controller::IControl* move, GameParty* gp,
		       unsigned int plidx)
{
  _sound.zPlay(Zik::PAUSE);
  _move = move;
  _val = 0;
  _timewait = 0.2f;
  _gp = gp;
  _idx = plidx;
}

Pause::~Pause()
{

}

void			Pause::initScreen(Screen::AScreen&)
{
}

int			Pause::Commands(gdl::Clock const& cl, gdl::Input& input)
{
  Controller::Button	but;

  _drawfnct = &Pause::drawCommand;
  _move->checkMove(input);
  but = _move->getBut();
  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_START
      && but != Controller::BUTTON_MODE)
    {
      Menus::MenusChoose(5, _val, static_cast<Controller::Peripheral*>(_move), _sound);
      _timewait = 0.09f;
      return (2);
    }
  _timewait = 0.2f;
  if (static_cast<Controller::Peripheral*>(_move)->getJoy()
      && but == Controller::BUTTON_PUTBOMB)
    {
      _pausePtr.push(_ptrfnct[1][_val + 1]);
    }
  else
    {
      _pausePtr.pop();
      _drawfnct = &Pause::drawPause;
    }
  return (2);
}

int			Pause::CommandsBomb(gdl::Clock const& cl, gdl::Input&)
{
  SDL_Event		event;
  Controller::Button	res;
  int			save;
  Controller::Peripheral* periph = static_cast<Controller::Peripheral*>(_move);

  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  while ((res = periph->retJoyBut()) == -1)
    SDL_WaitEvent(&event);
  save = periph->getValToBut(Controller::BUTTON_PUTBOMB);
  periph->setValToBut(Controller::BUTTON_PUTBOMB, periph->getValToBut(res));
  periph->setValToBut(res, save);
  _timewait = 0.5f;
  _pausePtr.pop();
  return (2);
}

int			Pause::CommandsMode(gdl::Clock const& cl, gdl::Input&)
{
  SDL_Event		event;
  Controller::Button	res;
  int			save;
  Controller::Peripheral* periph = static_cast<Controller::Peripheral*>(_move);

  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  while ((res = periph->retJoyBut()) == -1)
    SDL_WaitEvent(&event);
  save = periph->getValToBut(Controller::BUTTON_MODE);
  periph->setValToBut(Controller::BUTTON_MODE, periph->getValToBut(res));
  periph->setValToBut(res, save);
  _timewait = 0.5f;
  _pausePtr.pop();
  return (2);
}


int			Pause::CommandsStart(gdl::Clock const& cl, gdl::Input&)
{
  SDL_Event		event;
  Controller::Button	res;
  int			save;
  Controller::Peripheral* periph = static_cast<Controller::Peripheral*>(_move);

  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  while ((res = periph->retJoyBut()) == -1)
    SDL_WaitEvent(&event);
  save = periph->getValToBut(Controller::BUTTON_START);
  periph->setValToBut(Controller::BUTTON_START, periph->getValToBut(res));
  periph->setValToBut(res, save);
  _timewait = 0.5f;
  _pausePtr.pop();
  return (2);
}

int			Pause::CommandsUpCam(gdl::Clock const& cl, gdl::Input&)
{
  SDL_Event		event;
  Controller::Button	res;
  int			save;
  Controller::Peripheral* periph = static_cast<Controller::Peripheral*>(_move);

  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  while ((res = periph->retJoyBut()) == -1)
    SDL_WaitEvent(&event);
  save = periph->getValToBut(Controller::BUTTON_LEFTSHOULDER);
  periph->setValToBut(Controller::BUTTON_LEFTSHOULDER, periph->getValToBut(res));
  periph->setValToBut(res, save);
  _timewait = 0.5f;
  _pausePtr.pop();
  return (2);
}

int			Pause::CommandsDownCam(gdl::Clock const& cl, gdl::Input&)
{
  SDL_Event		event;
  Controller::Button	res;
  int			save;
  Controller::Peripheral* periph = static_cast<Controller::Peripheral*>(_move);

  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  while ((res = periph->retJoyBut()) == -1)
    SDL_WaitEvent(&event);
  save = periph->getValToBut(Controller::BUTTON_RIGHTSHOULDER);
  periph->setValToBut(Controller::BUTTON_RIGHTSHOULDER, periph->getValToBut(res));
  periph->setValToBut(res, save);
  _timewait = 0.5f;
  _pausePtr.pop();
  return (2);
}

int			Pause::WaitInPause(gdl::Clock const& cl, gdl::Input& input)
{
  Controller::Button	but;

  _move->checkMove(input);
  but = _move->getBut();
  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  if (but != Controller::BUTTON_PUTBOMB
      && but != Controller::BUTTON_START
      && but != Controller::BUTTON_MODE)
    {
      Menus::MenusChoose(3, _val, static_cast<Controller::Peripheral*>(_move), _sound);
      _timewait = 0.09f;
      return (2);
    }
  _timewait = 0.2f;
  if (but == Controller::BUTTON_PUTBOMB)
    {
      _pausePtr.push(_ptrfnct[_val][0]);
      _val = 0;
    }
  else
    _pausePtr.push(_ptrfnct[0][0]);
  return (2);
}

int		Pause::returnToGame(gdl::Clock const& cl, gdl::Input&)
{
  Menus::timeWaiting(_timewait, cl);
  if (_timewait > 0)
    return (2);
  _pausePtr.pop();
  return (1);
}

int		Pause::backToMenu(gdl::Clock const& cl, gdl::Input&)
{
  Menus::timeWaiting(_timewait, cl);
  _gp->stopIA();
  if (_timewait > 0)
    return (2);
  _pausePtr.pop();
  return (0);
}

int	Pause::update(gdl::Clock const& cl, gdl::Input& input)
{
  pausePtr	ptr = _pausePtr.top();
  int rt = (this->*ptr)(cl, input);
  return (rt);
}


bool	Pause::TranslatedSprite(Entity* gr, glm::vec3 const& vec,
				gdl::Clock const&, Screen::ASubScreen& scr,
				gdl::AShader& shader)
{
  GeometryDraw	*todraw;
  scr.apply(shader);
  if ((todraw = gr->getComponent<GeometryDraw>()))
    {
      glm::mat4		transform(1);
      glm::vec3 const&	pos(scr.getCamera()->getLookAt());

      glActiveTexture(GL_TEXTURE0);
      todraw->getToDraw()->getTexture().bind();
      transform = glm::translate(transform, pos + vec);
      transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
      todraw->getToDraw()->getGeometry()->draw(shader, transform, GL_QUADS);
    }
  return (true);
}

void	Pause::draw(Screen::AScreen& sc, gdl::Clock const&cl)
{
  _gp->draw(sc, cl);
  (this->*_drawfnct)(sc, cl);
}

void	Pause::drawPause(Screen::AScreen& sc, gdl::Clock const&cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-4.0f, 2.0f, -0.8f),
	glm::vec3(4.0f, 2.0f, -0.8f),
      },
      {
	glm::vec3(-5.0f, 2.0f, 1.0f),
	glm::vec3(5.0f, 2.0f, 1.0f),
      },
      {
	glm::vec3(-3.0f, 2.0f, 2.8f),
	glm::vec3(3.0f, 2.0f, 2.8f),
      }
    };

  DrawComponent::putsSubScreen("return", glm::vec3(0, 1, -1), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  DrawComponent::putsSubScreen("commands", glm::vec3(0, 1, 1), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  DrawComponent::putsSubScreen("menu", glm::vec3(0, 1, 3), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  TranslatedSprite(Menus::_background[3], tabvec[_val][0], cl,
		   *(sc.getScreens()[_idx]), sc.getShader());
  TranslatedSprite(Menus::_background[3], tabvec[_val][1], cl,
		   *(sc.getScreens()[_idx]), sc.getShader());
  glDisable(GL_ALPHA_TEST);
}

void	Pause::drawCommand(Screen::AScreen& sc, gdl::Clock const&cl)
{
  static glm::vec3 tabvec[][2] =
    {
      {
	glm::vec3(-4.8f, 2.0f, -4.5f),
	glm::vec3(-4.8f, 2.0f, -4.5f),
      },
      {
	glm::vec3(-4.8f, 2.0f, -2.5f),
	glm::vec3(-4.8f, 2.0f, -2.5f),
      },
      {
	glm::vec3(-4.8f, 2.0f, -0.8f),
	glm::vec3(-4.8f, 2.0f, -0.8f),
      },
      {
	glm::vec3(-4.8f, 2.0f, 1.1f),
	glm::vec3(-4.8f, 2.0f, 1.1f),
      },
      {
	glm::vec3(-4.8f, 2.0f, 3.0f),
	glm::vec3(-4.8f, 2.0f, 3.0f),
      }
    };
  std::string tabbutstr[] =
    {
      "a",
      "b",
      "x",
      "y",
      "back",
      "guide",
      "start",
      "lstick",
      "rstick",
      "lb",
      "rb",
      "pad up",
      "pad down",
      "pad left",
      "pad right"
    };

  std::ostringstream str;
  Controller::Peripheral* periph = static_cast<Controller::Peripheral*>(_move);

  str << "bombs " << tabbutstr[periph->getValToBut(Controller::BUTTON_PUTBOMB)];
  DrawComponent::putsSubScreen(str.str(), glm::vec3(-1, 1, -5), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  str.str(std::string());
  str << "mode  " << tabbutstr[periph->getValToBut(Controller::BUTTON_MODE)];
  DrawComponent::putsSubScreen(str.str(), glm::vec3(-1, 1, -3), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  str.str(std::string());
  str << "start " << tabbutstr[periph->getValToBut(Controller::BUTTON_START)];
  DrawComponent::putsSubScreen(str.str(), glm::vec3(1.4, 1, -1), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  str.str(std::string());
  str << "upcam " << tabbutstr[periph->getValToBut(Controller::BUTTON_LEFTSHOULDER)];
  DrawComponent::putsSubScreen(str.str(), glm::vec3(0.3, 1, 1), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  str.str(std::string());
  str << "dncam " << tabbutstr[periph->getValToBut(Controller::BUTTON_RIGHTSHOULDER)];
  DrawComponent::putsSubScreen(str.str(), glm::vec3(0.3, 1, 3), sc,
			       *(sc.getScreens()[_idx]), glm::vec3(1, 1, 0.5));
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  TranslatedSprite(Menus::_background[3], tabvec[_val][0], cl,
		   *(sc.getScreens()[_idx]), sc.getShader());
  TranslatedSprite(Menus::_background[3], tabvec[_val][1], cl,
		   *(sc.getScreens()[_idx]), sc.getShader());
  glDisable(GL_ALPHA_TEST);
}
