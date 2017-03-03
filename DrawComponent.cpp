#include <iostream>
#include "DrawComponent.hh"
#include "ConfigLoader.hpp"
#include "Entity.hpp"
#include "Position.hh"
#include "ModelDraw.hh"
#include "Except.hpp"

std::map<std::string, DrawComponent*> DrawComponent::_mapComponent;
std::map<char, DrawComponent*> DrawComponent::_mapLetters;
float const	DrawComponent::size_text = 1.2f;

DrawComponent::DrawComponent(DCptr ptr, std::string const& str, int const x, int const y)
{
  (this->*ptr)(str, x, y);
}

DrawComponent::DrawComponent(float x, float y, float xx, float yy)
{
  genLetters(x, y, xx, yy);
}

DrawComponent::~DrawComponent()
{}

void			DrawComponent::initialize()
{
  int background_size[2];
  int grass_size;
  float letter[4];
  std::string ground;
  std::string wall[2];
  std::string texture[2];
  char c;

  ConfigLoader::parseConfigFile("config/textures.cfg", "Textures");
  ConfigLoader::parseConfigFile("config/my_put_str.cfg", "Letters");

  ConfigLoader::getVarValue("Textures", "BACKGROUND_SIZE_X", background_size[0]);
  ConfigLoader::getVarValue("Textures", "BACKGROUND_SIZE_Y", background_size[1]);
  ConfigLoader::getVarValue("Textures", "BACKGROUND_GRASS_SIZE_X", grass_size);
  ConfigLoader::getVarValue("Textures", "GROUND", ground);
  ConfigLoader::getVarValue("Textures", "WALL", wall[0]);
  ConfigLoader::getVarValue("Textures", "UNWALL", wall[1]);
  ConfigLoader::getVarValue("Textures", "FIRE", texture[0]);

  c = 'a';
  while (c <= 'z')
    {
      std::ostringstream str[4];
      str[0] << c << "_xmin";
      ConfigLoader::getVarValue("Letters", str[0].str(), letter[0]);
      str[1] << c << "_xmax";
      ConfigLoader::getVarValue("Letters", str[1].str(), letter[1]);
      str[2] << c << "_ymin";
      ConfigLoader::getVarValue("Letters", str[2].str(), letter[2]);
      str[3] << c << "_ymax";
      ConfigLoader::getVarValue("Letters", str[3].str(), letter[3]);
      _mapLetters[c] = new DrawComponent(letter[0], letter[2], letter[1], letter[3]);
      ++c;
    }

  std::ostringstream str[4];
  str[0] << " _xmin";
  ConfigLoader::getVarValue("Letters", str[0].str(), letter[0]);
  str[1] << " _xmax";
  ConfigLoader::getVarValue("Letters", str[1].str(), letter[1]);
  str[2] << " _ymin";
  ConfigLoader::getVarValue("Letters", str[2].str(), letter[2]);
  str[3] <<" _ymax";
  ConfigLoader::getVarValue("Letters", str[3].str(), letter[3]);
  _mapLetters[' '] = new DrawComponent(letter[0], letter[2], letter[1], letter[3]);
  str[0].str(std::string());
  str[1].str(std::string());
  str[2].str(std::string());
  str[3].str(std::string());
  str[0] << ":_xmin";
  ConfigLoader::getVarValue("Letters", str[0].str(), letter[0]);
  str[1] << ":_xmax";
  ConfigLoader::getVarValue("Letters", str[1].str(), letter[1]);
  str[2] << ":_ymin";
  ConfigLoader::getVarValue("Letters", str[2].str(), letter[2]);
  str[3] <<":_ymax";
  ConfigLoader::getVarValue("Letters", str[3].str(), letter[3]);
  _mapLetters[':'] = new DrawComponent(letter[0], letter[2], letter[1], letter[3]);
  str[0].str(std::string());
  str[1].str(std::string());
  str[2].str(std::string());
  str[3].str(std::string());
  str[0] << "-_xmin";
  ConfigLoader::getVarValue("Letters", str[0].str(), letter[0]);
  str[1] << "-_xmax";
  ConfigLoader::getVarValue("Letters", str[1].str(), letter[1]);
  str[2] << "-_ymin";
  ConfigLoader::getVarValue("Letters", str[2].str(), letter[2]);
  str[3] <<"-_ymax";
  ConfigLoader::getVarValue("Letters", str[3].str(), letter[3]);
  _mapLetters['-'] = new DrawComponent(letter[0], letter[2], letter[1], letter[3]);
  c = '0';
  while (c <= '9')
    {
      std::ostringstream str[4];
      str[0] << c << "_xmin";
      ConfigLoader::getVarValue("Letters", str[0].str(), letter[0]);
      str[1] << c << "_xmax";
      ConfigLoader::getVarValue("Letters", str[1].str(), letter[1]);
      str[2] << c << "_ymin";
      ConfigLoader::getVarValue("Letters", str[2].str(), letter[2]);
      str[3] << c << "_ymax";
      ConfigLoader::getVarValue("Letters", str[3].str(), letter[3]);
      _mapLetters[c] = new DrawComponent(letter[0], letter[2], letter[1], letter[3]);
      ++c;
    }

  _mapComponent["Wall"] = new DrawComponent(&DrawComponent::genWall, wall[1], 0, 0);
  _mapComponent["UnWall"] = new DrawComponent(&DrawComponent::genUnWall, wall[1],0, 0);
  _mapComponent["Fire"] = new DrawComponent(&DrawComponent::genFire, texture[0], 0, 0);
  _mapComponent["Fire_Turn"] = new DrawComponent(&DrawComponent::genFire, FIRE_TURN_TEXTURE, 0, 0);
  _mapComponent["Fire_Cross"] = new DrawComponent(&DrawComponent::genFire, FIRE_CROSS_TEXTURE, 0, 0);
  _mapComponent["Fire_EndUp"] = new DrawComponent(&DrawComponent::genFire, FIRE_END_UP_TEXTURE, 0, 0);
  _mapComponent["Fire_EndRight"] = new DrawComponent(&DrawComponent::genFire, FIRE_END_RIGHT_TEXTURE, 0, 0);
  _mapComponent["Fire_EndLeft"] = new DrawComponent(&DrawComponent::genFire, FIRE_END_LEFT_TEXTURE, 0, 0);
  _mapComponent["Fire_EndDown"] = new DrawComponent(&DrawComponent::genFire, FIRE_END_DOWN_TEXTURE, 0, 0);

  _mapComponent["Skull"] = new DrawComponent(&DrawComponent::genBonus, SKULL, 0, 0);

  _mapComponent["BonusRange"] = new DrawComponent(&DrawComponent::genBonus, BONUS_RANGE, 0, 0);
  _mapComponent["MalusRange"] = new DrawComponent(&DrawComponent::genBonus, MALUS_RANGE, 0, 0);
  _mapComponent["BonusSpeed"] = new DrawComponent(&DrawComponent::genBonus, BONUS_SPEED, 0, 0);
  _mapComponent["MalusSpeed"] = new DrawComponent(&DrawComponent::genBonus, MALUS_SPEED, 0, 0);
  _mapComponent["BonusStock"] = new DrawComponent(&DrawComponent::genBonus, BONUS_STOCK, 0, 0);
  _mapComponent["MalusStock"] = new DrawComponent(&DrawComponent::genBonus, MALUS_STOCK, 0, 0);
  _mapComponent["PierceBomb"] = new DrawComponent(&DrawComponent::genBonus, PIERCE_BOMB, 0, 0);
  _mapComponent["KickBomb"] = new DrawComponent(&DrawComponent::genBonus, KICK_BOMB, 0, 0);
  _mapComponent["Teleport"] = new DrawComponent(&DrawComponent::genBonus, TELEPORT_BONUS, 0, 0);

  _mapComponent["Wall"] = new DrawComponent(&DrawComponent::genWall, wall[0], 0, 0);
  _mapComponent["UnWall"] = new DrawComponent(&DrawComponent::genUnWall, wall[1], 0, 0);

  _mapComponent["MenuStart1"] = new DrawComponent(&DrawComponent::genGround,
						  GENMENUSTART1, background_size[0], background_size[1]);
  _mapComponent["MenuStart2"] = new DrawComponent(&DrawComponent::genGround, GENMENUSTART2, background_size[0], background_size[1]);
  _mapComponent["MenuVirgin"] = new DrawComponent(&DrawComponent::genGround, GENMENUVIRGIN, background_size[0], background_size[1]);

  _mapComponent["MenuCredits"] = new DrawComponent(&DrawComponent::genGround, GENMENUCREDITS, background_size[0], background_size[1]);

  _mapComponent["MenuMain"] = new DrawComponent(&DrawComponent::genGround, GENMENUMAIN, background_size[0], background_size[1]);
  _mapComponent["MenuPlay"] = new DrawComponent(&DrawComponent::genGround, GENMENUPLAY, background_size[0], background_size[1]);
  _mapComponent["MenuBomb"] = new DrawComponent(&DrawComponent::genGround, GENMENUBOMB, 2, 2);
  _mapComponent["Ground"] = new DrawComponent(&DrawComponent::genGround, ground, 47, 36);
}

gdl::Texture const&	DrawComponent::getTexture() const
{
  return _texture;
}

gdl::Geometry *DrawComponent::getGeometry() const
{
  return _geometry;
}

DrawComponent const* DrawComponent::getComponent(std::string const& str)
{
  DrawComponent* DC = _mapComponent[str];
  return (DC);
}

void	DrawComponent::genWall(std::string const& str, int const, int const)
{
  _geometry = new gdl::Geometry;
  _geometry->pushVertex(glm::vec3(0.5f, 0.0f, 0.5f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.5f, 0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.5f, 0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.0f, 0.5f));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.0f, -0.5f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.0f, -0.5f));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.0f, -0.5f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.5f, 0.5f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.0f, 0.5f));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.0f, 0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.5f, 0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.0f, -0.5f));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.5f, 0.5f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.5f, 0.5f));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.0f, -0.5f));
  _geometry->pushVertex(glm::vec3(0.5f, 0.0f, 0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.0f, 0.5f));
  _geometry->pushVertex(glm::vec3(-0.5f, 0.0f, -0.5f));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->build();

  _texture.load(str);
}

void	DrawComponent::genUnWall(std::string const& str, int const, int const)
{
  genWall(str);
}

void	DrawComponent::genFire(std::string const& str, int const, int const)
{
  genWall(str);
}

void	DrawComponent::genGround(std::string const& str, int const x, int const y)
{
  _geometry = new gdl::Geometry;
  _geometry->pushVertex(glm::vec3(-x / 2, 0, -y / 2));
  _geometry->pushVertex(glm::vec3(-x / 2, 0, y / 2));
  _geometry->pushVertex(glm::vec3(x / 2, 0, y / 2));
  _geometry->pushVertex(glm::vec3(x / 2, 0, -y / 2));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));
  if (_texture.load(str) == false)
    {
      throw BombermanException("Cannot load the cube texture : " + str);
    }
  _geometry->build();
}

void	DrawComponent::genBonus(std::string const& str, int const, int const)
{
  genWall(str);
}

#include <iomanip>

void	DrawComponent::genLetters(float x, float y, float xx, float yy)
{
  float	img_size[2];
  std::string str;

  ConfigLoader::getVarValue("Textures", "LETTERS", str);
  ConfigLoader::getVarValue("Letters", "img_dimension_x", img_size[0]);
  ConfigLoader::getVarValue("Letters", "img_dimension_y", img_size[1]);

  int i = 10;

  x = x * i / img_size[0];
  y = y * i / img_size[1];
  xx = xx * i / img_size[0];
  yy = yy * i / img_size[1];

  _geometry = new gdl::Geometry;
  _geometry->pushVertex(glm::vec3(0, 0, 0));
  _geometry->pushVertex(glm::vec3(0, 0, 1.4));
  _geometry->pushVertex(glm::vec3(1.4, 0, 1.4));
  _geometry->pushVertex(glm::vec3(1.4, 0, 0));
  _geometry->pushUv(glm::vec2(x, yy));
  _geometry->pushUv(glm::vec2(x, y));
  _geometry->pushUv(glm::vec2(xx, y));
  _geometry->pushUv(glm::vec2(xx, yy));
  if (_texture.load(str) == false)
    {
      throw BombermanException("Cannot load the cube texture : " + str);
    }
  _geometry->build();
}

void	DrawComponent::putstring(const std::string &str, glm::vec3 vec,
				 Screen::AScreen &screen, const gdl::Clock &clock)
{
  int count;
  Entity *e;
  GeometryDraw *c;
  Position* pos;

  count = 0;
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  while (str[count])
    {
      e = new Entity;
      e->addComponent(new Position(NULL));
      e->addComponent(new GeometryDraw(str[count]));
      c = e->getComponent<GeometryDraw>();
      if ((pos = e->getComponent<Position>()))
	{
	  pos->getPos() = vec;
	  vec.x += 1.2f;
	}
      c->draw(screen, clock);
      ++count;
      delete e;
    }
  glDisable(GL_ALPHA_TEST);
}

void	DrawComponent::putsSubScreen(std::string const& str, glm::vec2 const& pos,
				     Screen::AScreen &scr,
				     Screen::ASubScreen const& subscr,
				     glm::vec3 const& scalevec)
{
  int		count;
  glm::vec3	vec(subscr.getCamera()->getLookAt());
  glm::vec2	const center(subscr.getCenter());

  count = 0;
  subscr.apply(scr.getShader());
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  vec.x -= size_text * (str.size() / 2) * scalevec.x;
  glViewport(center.x + pos.x - SCREENX / 2, center.y + pos.y - SCREENY / 2, SCREENX, SCREENY);
  while (str[count])
    {
      DrawComponent	const*	_toDraw = DrawComponent::getLetter(str[count]);
      glm::mat4		transform(1);

      glActiveTexture(GL_TEXTURE0);
      _toDraw->getTexture().bind();
      transform = glm::translate(transform, glm::vec3(vec.x, 1, vec.z));
      transform = glm::scale(transform, scalevec);
      _toDraw->getGeometry()->draw(scr.getShader(), transform, GL_QUADS);
      vec.x += size_text * scalevec.x;
      ++count;
    }
  glDisable(GL_ALPHA_TEST);
}

void	DrawComponent::putsSubScreen(std::string const& str, glm::vec3 const& pos,
				     Screen::AScreen &scr,
				     Screen::ASubScreen const& subscr,
				     glm::vec3 const& scalevec)
{
  int		count;
  glm::vec3	vec(subscr.getCamera()->getLookAt());

  count = 0;
  subscr.apply(scr.getShader());
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.0f);
  vec.x -= DrawComponent::size_text * (str.size() / 2) * scalevec.x;
  while (str[count])
    {
      DrawComponent	const*	_toDraw = DrawComponent::getLetter(str[count]);
      glm::mat4		transform(1);

      glActiveTexture(GL_TEXTURE0);
      _toDraw->getTexture().bind();
      transform = glm::translate(transform, glm::vec3(vec.x + pos.x, pos.y, vec.z + pos.z));
      transform = glm::scale(transform, scalevec);
      _toDraw->getGeometry()->draw(scr.getShader(), transform, GL_QUADS);
      vec.x += DrawComponent::size_text * scalevec.x;
      ++count;
    }
  glDisable(GL_ALPHA_TEST);
}

DrawComponent const* DrawComponent::getLetter(char c)
{
  DrawComponent* DC = _mapLetters[c];
  return (DC);
}
