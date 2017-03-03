#include "Direction.hh"
#include "utils.hh"

Direction::t const Direction::all[4] =
  {
    UP,
    LEFT,
    RIGHT,
    DOWN
  };

static int const	g_dxdys[][2] =
  {
    {0, -1},
    {-1, 0},
    {1, 0},
    {0, 1}
  };

int const *		Direction::convert_to_cartesian(enum t val)
{
  if (val < LEN(all))
    return (g_dxdys[val]);
  return (0);
}
