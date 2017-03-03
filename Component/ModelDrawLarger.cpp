#include "Position.hh"
#include "Move.hh"
#include "Entity.hpp"
#include "ModelDrawLarger.hh"

void	ModelDrawLarger::draw(Screen::AScreen &screen, gdl::Clock const& clock)
{
  int i;

  i = 3;
  _drawmodel->getRatio() += (_state ? -i : i) * ((clock.getElapsed() * _largeRatio));
  ModelDraw::draw(screen, clock);
  if (_drawmodel->getRatio().x > 0.0045)
    _state = true;
  if (_drawmodel->getRatio().x < 0.0040)
    _state = false;
}
