#include "RotateDraw.hh"
#include "Position.hh"
#include "Entity.hpp"

RotateDraw::RotateDraw(std::string const& str)
  : GeometryDraw(str), _angle(0)
{
}

RotateDraw::RotateDraw(std::istream & is)
  : GeometryDraw(is), _angle(0)
{
}

void	RotateDraw::saveSelf(std::ostream &os) const
{
  os << "RotateDraw " << _name << std::endl;
}

void RotateDraw::draw(Screen::AScreen &screen, gdl::Clock const &clock)
{
  glm::mat4 transform(1);
  Position	*pos;

  if ((pos = _owner->getComponent<Position>()))
    transform = glm::translate(transform, pos->getPos());
  transform = glm::rotate(transform, _angle, glm::vec3(0, 1, 0));
  transform = glm::scale(transform, glm::vec3(0.75f, 0.75f, 0.75f));
  _angle = _angle + 90.0f * clock.getElapsed();
  if (_angle > 360.0f)
    _angle = 0;
  if (pos)
    draw_in_screen(screen, pos->getPos(), transform);
}
