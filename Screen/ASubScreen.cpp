#include "ASubScreen.hh"
#include "AScreen.hh"

Screen::ASubScreen::ASubScreen(ACamera *camera)
  : _pos(0, 0), _size(SCREENX, SCREENY), _camera(camera)
{
}

bool	Screen::ASubScreen::isInScreen(glm::vec3 const& pos3d,
				       glm::vec3 const& size3d) const
{
  glm::vec2	range(_camera->range(_size));
  glm::vec3	diff(pos3d - _camera->getLookAt());

  if ((diff.x + range.x >= -size3d.x / 2 && diff.x - range.x <= size3d.x / 2 &&
       diff.z + range.y >= -size3d.z / 2 && diff.z - range.y <= size3d.z / 2))
    {
      return (true);
    }
  return (false);
}

glm::vec2	Screen::ASubScreen::getCenter() const
{
  return (glm::vec2(_pos.x + _size.x / 2,
		    _pos.y + _size.y / 2));
}

void	Screen::ASubScreen::apply(gdl::AShader& shader) const
{
  glm::vec2	center(_pos.x + _size.x / 2,
		       _pos.y + _size.y / 2);

  glViewport(center.x - SCREENX / 2, center.y - SCREENY / 2, SCREENX, SCREENY);
  glScissor(_pos.x + _size.x / 32, _pos.y + _size.y / 32,
	    _size.x / 32 * 30, _size.y / 32 * 30);
  _camera->apply(shader);
}

Screen::ASubScreen::~ASubScreen()
{
  delete _camera;
}
