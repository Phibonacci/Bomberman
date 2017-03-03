#include "GameIntro.hh"
#include "AFullScreen.hpp"
#include "DrawComponent.hh"
#include "Entity.hpp"
#include "Position.hh"
#include "ModelDraw.hh"

Intro::GameIntro::GameIntro()
  : _introtime(10.0f), _cam(NULL),
    _person(new Entity)
{
  _person->addComponent(new Position(NULL, glm::vec3(0, 0, 0)));
  _person->addComponent(new ModelDraw("Bomberman"));
  _person->getComponent<ModelDraw>()->setCurrentAnime("running");
}

Intro::GameIntro::~GameIntro()
{
  delete _person;
}

void Intro::GameIntro::initScreen(Screen::AScreen &scr)
{
  _cam = new Screen::ACamera;
  scr.cleanScreens();
  _cam->getLookAt() = glm::vec3(0, 10, 0.0);
  scr.addScreen(new Screen::AFullScreen(_cam));
}

int	Intro::GameIntro::update(gdl::Clock const& clock, gdl::Input &input)
{
  _introtime -= clock.getElapsed();
  if (_cam->getLookAt().y - clock.getElapsed() * 10 > 0)
    _cam->getLookAt().y -= clock.getElapsed() * 10;
  _cam->getCameraDiff().z += clock.getElapsed() * 5;
  if (_introtime <= 0 || input.getKey(SDLK_SPACE))
    return (0);
  return (4);
}

void Intro::GameIntro::draw(Screen::AScreen &screen, gdl::Clock const &clock)
{
  glClearColor(1 * _introtime / 10, (10 - _introtime) / 10,
	       (_introtime) / 20, 0);
  _person->draw(screen, clock);
}
