#include "Player.hh"
#include "Peripheral.hh"

Player::Player(bool isPlayer)
  : _bombCount(1), _bombRange(2), _score(0),
    _speed(3.0f), _control(0), _bombType(BombType::NORMAL)
{
  static maRand		random;

  float r[3];
  r[0] = random.getRand(0, 100) / 100.0f;
  r[1] = random.getRand(0, 100) / 100.0f;
  r[2] = random.getRand(0, 100) / 100.0f;

  glEnable(GL_DEPTH_TEST);
  _shader.load("./shaders/bomber.fp", GL_FRAGMENT_SHADER);
  _shader.load("./shaders/basic.vp", GL_VERTEX_SHADER);
  _shader.build();
  _color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  if (isPlayer == true)
    _color = glm::vec4(r[0], r[1], r[2], 1.0f);

}

void	Player::load(std::istream &is)
{
  int save;

  is >> _bombCount >> _bombRange >> _score >> _speed
     >> save >> _color.x >> _color.y >> _color.z >> _color.w;
  _bombType = static_cast<BombType::BTYPE>(save);
}

void	Player::saveSelf(std::ostream &os) const
{
  os << "Player " << _bombCount << " "
     << _bombRange << " " << _score << " " << _speed << " "
     << " " << _bombType << " " << _color.x << " " << _color.y
     << " " << _color.z << " " << _color.z << std::endl;
}

bool	Player::isUser() const
{
  Controller::Peripheral	*user;

  if (_control && (user = dynamic_cast<Controller::Peripheral*>(_control)))
    return (true);
  return (false);
}
