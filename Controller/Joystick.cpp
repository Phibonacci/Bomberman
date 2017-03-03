/**
 * @file Joystick.cpp
 */
#include <iostream>
#include <SDL2/SDL_gamecontroller.h>
#include "Joystick.hh"

int Controller::Joystick::_nJoyUse = 0;
int Controller::Joystick::_nKeyboardUse = 0;

Controller::Joystick::Joystick(int const nbJoy)
{
  _joy = NULL;
  _save = NULL;
  if (_nJoyUse < SDL_NumJoysticks())
    {
      if ((_joy = SDL_GameControllerOpen(nbJoy)) == NULL)
	{
	  _save = SDL_JoystickOpen(nbJoy);
	}
      _nJoyUse++;
    }

  _tabButVal[BUTTON_INVALID] = -1;
  _tabButVal[BUTTON_PUTBOMB] = 0;
  _tabButVal[BUTTON_MODE] = 1;
  _tabButVal[BUTTON_X] = 2;
  _tabButVal[BUTTON_Y] = 3;
  _tabButVal[BUTTON_BACK] = 4;
  _tabButVal[BUTTON_GUIDE] = 5;
  _tabButVal[BUTTON_START] = 6;
  _tabButVal[BUTTON_LEFTSTICK] = 7;
  _tabButVal[BUTTON_RIGHTSTICK] = 8;
  _tabButVal[BUTTON_LEFTSHOULDER] = 9;
  _tabButVal[BUTTON_RIGHTSHOULDER] = 10;
  _tabButVal[BUTTON_DPAD_UP] = 11;
  _tabButVal[BUTTON_DPAD_DOWN] = 12;
  _tabButVal[BUTTON_DPAD_LEFT] = 13;
  _tabButVal[BUTTON_DPAD_RIGHT] = 14;
}

Controller::Joystick::~Joystick()
{
  if (_joy)
    _nJoyUse--;
  else
    _nKeyboardUse--;
  SDL_GameControllerClose(_joy);
}

SDL_Joystick*	Controller::Joystick::getJoy() const
{
  if (_joy)
    return SDL_GameControllerGetJoystick(_joy);
  return (_save);
}

SDL_GameController*	Controller::Joystick::getControl()
{
  return _joy;
}

int		Controller::Joystick::getValToBut(Button but) const
{
  int rt = -1;
  if (but >= 0 && but <= 14)
    rt = _tabButVal.at(but);
  return rt;
}

void		Controller::Joystick::setValToBut(Button const but,
					  int const val)
{
  _tabButVal[but] = val;
}
