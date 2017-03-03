#include "ACamera.hh"
#include "Position.hh"
#include "Entity.hpp"
#include "Player.hh"

glm::mat4 const	Screen::ACamera::projection =
  glm::perspective(60.0f, 8.0f / 6.0f, 0.1f, 100.0f);

Screen::ACamera::ACamera()
  : _lookAt(0, 0, 0), _cameraDiff(glm::vec3(0, 15, 0.1))
{
}

glm::mat4 Screen::ACamera::getTransformation() const
{
  return (glm::lookAt(_lookAt + _cameraDiff,
		      _lookAt, glm::vec3(0, 1, 0)));
}

glm::vec3	&Screen::ACamera::getLookAt()
{
  return _lookAt;
}

glm::vec3	&Screen::ACamera::getCameraDiff()
{
  return _cameraDiff;
}

#include <iostream>

glm::vec2	Screen::ACamera::range(glm::vec2 const& size) const
{
  return (glm::vec2(size.x / 199, size.y / 120));
}

void Screen::ACamera::apply(gdl::AShader &shader)
{
  shader.setUniform("view",
		    getTransformation());
  shader.setUniform("projection",
		    projection);
  shader.bind();
}

Screen::AutoCamera::AutoCamera(Player *pl)
  : _tofollow(pl)
{
}

void		Screen::AutoCamera::update()
{
  Position	*pos;

  if (_tofollow && (_tofollow->getPerson()) &&
      (pos = _tofollow->getPerson()->getComponent<Position>()))
    {
      glm::vec3	const diff(pos->getPos() - _lookAt);

      _lookAt += diff / 16.0f;
    }
}
