#include "ModelDraw.hh"
#include "Position.hh"
#include "Move.hh"
#include "Entity.hpp"
#include "HasPlayer.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>

ModelDraw::ModelDraw(std::istream &is)
{
  is >> _name;
  _drawmodel = DrawModel::getDrawModel(_name);
}

GeometryDraw::GeometryDraw(std::istream & is)
{
  is >> _name;
  _toDraw = DrawComponent::getComponent(_name);
}

void ModelDraw::saveSelf(std::ostream &os) const
{
  os << "ModelDraw " << _name << std::endl;
}

void GeometryDraw::saveSelf(std::ostream &os) const
{
  os << "GeometryDraw " << _name << std::endl;
}

ModelDraw::ModelDraw(std::string const& str)
  : _name(str)
{
  _drawmodel = DrawModel::getDrawModel(str);
}

void ModelDraw::draw(Screen::AScreen &screen, gdl::Clock const &clock)
{
  gdl::AShader	&shader(screen.getShader());
  glm::mat4	transform(1);
  HasPlayer	*player;
  gdl::AShader	*sha;

  Position	*pos;
  if ((pos = _owner->getComponent<Position>()))
    transform = glm::translate(transform, pos->getPos());

  if (screen.isInAnyScreen(pos->getPos(), glm::vec3(0.5, 0, 0.5)))
    {
      if ((player = _owner->getComponent<HasPlayer>()))
	sha = &player->getPlayer()->getShader();
      else
	sha = &shader;

      AMove		*move;
      if ((move = _owner->getComponent<Move>()))
	{
	  float angle = move->getAngle();

	  transform = glm::rotate(transform, angle, glm::vec3(0, 1, 0));
	}
      transform = glm::scale(transform, _drawmodel->getRatio());

      {
      std::list<Screen::ASubScreen*>::const_iterator it;

      sha->bind();
      if (player)
	sha->setUniform("uColor", player->getPlayer()->getColor());
      screen.initScreensIn(pos->getPos(), glm::vec3(0.5, 0, 0.5));
      it = screen.inBegin();
      while (it != screen.inEnd())
	{
	  (*it)->apply(*sha);
	  if (it == screen.inBegin())
	    _drawmodel->getModel().draw(*sha, transform, clock.getElapsed());
	  else
	    _drawmodel->getModel().draw(*sha, transform, 0);
	  ++it;
	}
      }
    }
}

void		ModelDraw::setCurrentAnime(std::string const &anime)
{
  _drawmodel->getModel().setCurrentSubAnim(anime);
}

ModelDraw::~ModelDraw()
{
  delete _drawmodel;
}

GeometryDraw::GeometryDraw(std::string const &str)
  : _name(str), _toDraw(DrawComponent::getComponent(str))
{
}

GeometryDraw::GeometryDraw(char c)
  : _toDraw(DrawComponent::getLetter(c))
{
}

void GeometryDraw::draw_in_screen(Screen::AScreen &screen,
				  glm::vec3 const& pos,
				  glm::mat4 const& transform)
{
  gdl::AShader	&shader(screen.getShader());

  if (screen.isInAnyScreen(pos, glm::vec3(4, 0, 4)))
    {
      std::list<Screen::ASubScreen*>::const_iterator it;

      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0.0f);
      glActiveTexture(GL_TEXTURE0);
      _toDraw->getTexture().bind();

      screen.initScreensIn(pos, glm::vec3(4, 0, 4));
      it = screen.inBegin();
      shader.bind();
      while (it != screen.inEnd())
	{
	  (*it)->apply(shader);
	  _toDraw->getGeometry()->draw(shader, transform, GL_QUADS);
	  ++it;
	}
      glDisable(GL_ALPHA_TEST);
    }
}

void GeometryDraw::draw(Screen::AScreen &screen, gdl::Clock const &)
{
  glm::mat4	transform(1);
  Position	*pos;

  if ((pos = _owner->getComponent<Position>()))
    transform = glm::translate(transform, pos->getPos());
  if (pos)
    draw_in_screen(screen, pos->getPos(), transform);
}
