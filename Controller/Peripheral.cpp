/**
 * @file Peripheral.cpp
 */
#include <stdexcept>
#include <iostream>
#include "Peripheral.hh"
#include "Except.hpp"

Controller::Peripheral::Peripheral(int nbJoy, size_t sensi)
  : Joystick(nbJoy), _but(BUTTON_INVALID),
    _dir(),  _playerkeys(), _sensi(sensi)
{
  if (_joy == NULL && _save == NULL)
    {
      saveKeys();
      displaySaveKeys();
    }
}

Controller::Peripheral::~Peripheral()
{
}

void	Controller::Peripheral::setDir(enum Controller::Peripheral::e_dir)
{
}

void	Controller::Peripheral::setBut(Controller::Button but)
{
  _but = but;
}

PlayerDir const&	Controller::Peripheral::getDir() const
{
  return _dir;
}

Controller::Button	Controller::Peripheral::getBut()
{
  return _but;
}

Controller::Button	Controller::Peripheral::retJoyButton()
{
  SDL_Joystick * joy = getJoy();

  for (register int i = static_cast<int>(BUTTON_MAX); i >= 0 ; i--)
    {
      if (SDL_JoystickGetButton(joy, static_cast<SDL_GameControllerButton>(i)))
	return (static_cast<Button>(i));
    }
  return (BUTTON_INVALID);
}

Controller::Button	Controller::Peripheral::retJoyBut()
{
  register SDL_GameController *getJoy = getControl();

  if (!getJoy)
    return (retJoyButton());
  for (register int i = static_cast<int>(BUTTON_MAX); i >= 0 ; i--)
    {
      if (SDL_GameControllerGetButton(getJoy, static_cast<SDL_GameControllerButton>(i)))
	return (static_cast<Controller::Button>(getValToBut
						(static_cast<Controller::Button>(i))));
    }
  return (BUTTON_INVALID);
}

void	Controller::Peripheral::saveKeys()
{
  if (_nKeyboardUse == 0)
    {
      _playerkeys[0] = SDLK_LEFT;
      _playerkeys[1] = SDLK_RIGHT;
      _playerkeys[2] = SDLK_DOWN;
      _playerkeys[3] = SDLK_UP;
      _playerkeys[4] = SDLK_KP_0;
      _playerkeys[5] = SDLK_KP_1;
      _playerkeys[6] = SDLK_KP_2;
      _playerkeys[9] = SDLK_KP_6;
      _playerkeys[10] = SDLK_KP_9;
    }
  else if (_nKeyboardUse == 1)
    {
      _playerkeys[0] = SDLK_a;
      _playerkeys[1] = SDLK_d;
      _playerkeys[2] = SDLK_s;
      _playerkeys[3] = SDLK_w;
      _playerkeys[4] = SDLK_TAB;
      _playerkeys[5] = SDLK_q;
      _playerkeys[6] = SDLK_r;
      _playerkeys[9] = SDLK_g;
      _playerkeys[10] = SDLK_t;
    }
  else
    throw ExceptController();
  _playerkeys[7] = SDLK_RETURN;
  _playerkeys[8] = SDLK_SPACE;
}

void	Controller::Peripheral::displaySaveKeys()
{
  _nKeyboardUse++;
}

bool	Controller::Peripheral::checkKeys(gdl::Input& input)
{
  Controller::Button	buttab[] =
    {
      BUTTON_PUTBOMB,
      BUTTON_MODE,
      BUTTON_X,
      BUTTON_START,
      BUTTON_BACK,
      BUTTON_RIGHTSHOULDER,
      BUTTON_LEFTSHOULDER
    };

  _but = BUTTON_INVALID;
  for (register size_t i = _playerkeys.size() - 1 ; i >= 4 ; i--)
    if (input.getInput(_playerkeys[i]))
      {
	_but = buttab[i - 4];
	break ;
      }
  double tabangle[] = {0.0f, -90.0f, 90.0f, 0.0f, 180.0f};
  _dir.setAngle(0);
  _dir.setSpeed(0);
  for (register size_t i = 4; i--;)
    if (input.getInput(_playerkeys[i]))
      {
	_dir.setAngle(tabangle[i + 1]);
	_dir.setSpeed(static_cast<int>(RAYON));
	return (true);
      }
  return (false);
}

void	Controller::Peripheral::checkHat()
{
  Uint8 check[] = {SDL_HAT_CENTERED,
		   SDL_HAT_LEFT,
		   SDL_HAT_RIGHT,
		   SDL_HAT_DOWN,
		   SDL_HAT_UP};
  double tabval[] = {0.0f, -90.0f, 90.0f, 0.0f, 180.0f};
  Uint8 hatValue = SDL_JoystickGetHat(getJoy(), 0);

  for (register size_t test = sizeof(check) / sizeof(check[0]); test--;)
    {
      if (hatValue == check[test])
	{
	  _dir.setAngle(tabval[test]);
	  _dir.setSpeed((test == 0 ? 0 : static_cast<int>(RAYON)));
	  break ;
	}
    }
}

#define ABS(x) ((x) < 0 ? (-x) : (x))
bool	Controller::Peripheral::checkAxes()
{
  Sint16 x = SDL_JoystickGetAxis(getJoy(), SDL_CONTROLLER_AXIS_LEFTX);
  Sint16 y = SDL_JoystickGetAxis(getJoy(), SDL_CONTROLLER_AXIS_LEFTY);

  if (ABS(x) > static_cast<Sint16>(_sensi) || ABS(y) > static_cast<Sint16>(_sensi))
    {
      _dir.xyToAngle(x, -y);
      _dir.setSpeed((ABS(x) > ABS(y) ? ABS(x) : ABS(y)));
      return (true);
    }
  return (false);
}

void	Controller::Peripheral::changeBut()
{
}

int	Controller::Peripheral::checkJoyButton()
{
  SDL_Joystick * joy = getJoy();

  for (register int i = static_cast<int>(BUTTON_MAX); i >= 0 ; i--)
    {
      if (SDL_JoystickGetButton(joy, static_cast<SDL_GameControllerButton>(i)))
	{
	  _but = static_cast<Button>(i);
	  break ;
	}
    }
  return (-1);
}

int	Controller::Peripheral::checkButtons()
{
  register SDL_GameController *getJoy = getControl();

  _but = Controller::BUTTON_INVALID;
  if (!getJoy)
    return (checkJoyButton());
  for (register int i = static_cast<int>(BUTTON_MAX); i >= 0 ; i--)
    {
      if (SDL_GameControllerGetButton(getJoy, static_cast<SDL_GameControllerButton>(i)))
	{
	  _but = static_cast<Controller::Button>(getValToBut(static_cast<Controller::Button>(i)));
	  break ;
	}
    }
  return (-1);
}

void	Controller::Peripheral::setSensi(size_t sensi)
{
  _sensi = sensi;
}

size_t	Controller::Peripheral::getSensi() const
{
  return _sensi;
}

bool	Controller::Peripheral::getUseJoy() const
{
  return (_joy != NULL);
}

void	Controller::Peripheral::checkMove(gdl::Input& input)
{
  if (_joy == NULL && _save == NULL)
    checkKeys(input);
  else
    {
      SDL_JoystickUpdate();
      checkButtons();
      if (checkAxes() == false)
	checkHat();
    }
}
