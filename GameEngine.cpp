#include <iostream>
#include <unistd.h>
#include "GameEngine.hh"
#include "GameParty.hh"
#include "DrawComponent.hh"
#include "DrawModel.hh"
#include "Pause.hpp"
#include "MapEditor.hpp"
#include "MasterController.hpp"
#include "Info.hpp"
#include "Except.hpp"
#include "GameIntro.hh"

Zik GameEngine::_sound;

GameEngine::GameEngine() : _screen()
{
  ConfigLoader::parseConfigFile("config/animations.cfg", "animations");

  _scenes[0] = NULL;
  _scenes[1] = NULL;
  _scenes[2] = NULL;
  _scenes[3] = NULL;
  _scenes[4] = NULL;
  _current = 4;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);
  _context.flush();
  if (!_context.start(SCREENX, SCREENY, "My bomberman!", SDL_INIT_EVERYTHING))
    throw BombermanException("Cant start sdl context");
}

bool	GameEngine::initialize()
{
  _sound.initialize();
  if (!_screen.initialize())
    return (false);
  Controller::MasterController::initialize();
  DrawComponent::initialize();
  DrawModel::initialize();
  _scenes[2] = new Pause(_sound);
  _scenes[1] = new GameParty(static_cast<Pause*>(_scenes[2]));
  _scenes[3] = new MapEditor(static_cast<GameParty*>(_scenes[1]));
  _scenes[0] = new Menus(_info, static_cast<GameParty*>(_scenes[1]),
			 _sound, static_cast<MapEditor*>(_scenes[3]));
  _scenes[4] = new Intro::GameIntro();
  _scenes[_current]->initScreen(_screen);
  return (true);
}

void	GameEngine::changeCurrent(int current)
{
  if (current == 1 && _current == 2)
    ;
  else
    {
      (_scenes[current])->initScreen(_screen);
    }
  _current = current;
}

bool	GameEngine::update()
{
  int	current;

  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  _context.updateInputs(_input);
  _context.updateClock(_clock);
  if ((current = _scenes[_current]->update(_clock, _input)) == -1)
    return false;
  if (current != _current)
    changeCurrent(current);
  return true;
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);

  _scenes[_current]->draw(_screen, _clock);
  _context.flush();
}

GameEngine::~GameEngine()
{
}
