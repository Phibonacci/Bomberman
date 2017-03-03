#include "PlayerDir.hpp"
#include <math.h>
#include <iostream>

PlayerDir::PlayerDir()
  : _angle(0.0f), _speed(0)
{}

PlayerDir::~PlayerDir()
{}

void PlayerDir::xyToAngle(int x, int y)
{
  _angle = static_cast<float>(atan2(static_cast<double>(y),
				    static_cast<double>(x)) * (180.0 / M_PI));
  _angle += 90;
}

void		PlayerDir::setSpeed(int speed)
{
  _speed = static_cast<float>(speed) / RAYON;
}

void		PlayerDir::setAngle(float const& angle)
{
  _angle = angle;
}

void		PlayerDir::setSpeed(float speed)
{
  _speed = speed;
}

float const&	PlayerDir::getAngle() const
{
  return _angle;
}

float const&	PlayerDir::getSpeed() const
{
  return _speed;
}
