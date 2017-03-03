#include "AScreen.hh"
#include <algorithm>

Screen::AScreen::inScreen::inScreen(glm::vec3 const &pos,
				    glm::vec3 const& size,
				    std::list<Screen::ASubScreen*> *store)
  : _pos3d(pos), _size3d(size), _store(store)
{
}

bool	Screen::AScreen::inScreen::operator()(Screen::ASubScreen *target)
{
  bool	rt;

  if ((rt = target->isInScreen(_pos3d, _size3d)) && _store)
    {
      _store->push_back(target);
    }
  return (rt);
}


Screen::AScreen::AScreen()
  : _shader()
{
}

bool	Screen::AScreen::initialize()
{
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);
  _shader.bind();
  return (true);
}

bool Screen::AScreen::isInAnyScreen(glm::vec3 const& pos3d,
				    glm::vec3 const& size3d) const
{
  return (std::find_if(_screens.begin(), _screens.end(),
		       inScreen(pos3d, size3d, NULL)) != _screens.end());
}

void	Screen::AScreen::initScreensIn(glm::vec3 const& pos3d,
		      glm::vec3 const& size3d)
{
  _inScreens.clear();
  std::for_each(_screens.begin(), _screens.end(),
		inScreen(pos3d, size3d, &_inScreens));
}

bool	Screen::AScreen::addScreen(ASubScreen *a)
{
  _screens.push_back(a);
  return (true);
}

void	Screen::AScreen::Updater::operator()(ASubScreen *target)
{
  ACamera	*c = target->getCamera();

  if (c)
    c->update();
}

void	Screen::AScreen::update()
{
  std::for_each(_screens.begin(), _screens.end(),
		Updater());
}

static void	destroy(Screen::ASubScreen *&t)
{
  delete t;
  t = NULL;
}

#include <iostream>

void	Screen::AScreen::cleanScreens()
{
  std::for_each(_screens.begin(), _screens.end(), ::destroy);
  _screens.clear();
}

Screen::AScreen::~AScreen()
{
  std::for_each(_screens.begin(), _screens.end(), ::destroy);
}
