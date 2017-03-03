#include <vector>
#include <iostream>
#include <stdexcept>

#include "Except.hpp"
#include "Case.hh"
#include "Content.hh"

int				Content::getSpawn(std::vector<std::vector<Types> > &temp,
						  int maxx, int maxy, int startx,
						  int starty, int &placed)
{
  int				dir;
  std::vector<Case::DirWall>	dto;
  static int			count = 0;
  int				cx = startx;
  int				cy = starty;

  this->getDirSpawn(maxx, maxy, dto, temp, cx, cy);
  if (count == 4){
    count = 0;
    temp[startx][starty] = SPAWN;
    ++placed;
    return 1;
  }
  if (dto.size() > 0){
    dir = rand.getRand(0, dto.size());
    dir = dto[dir];
    int i = 0;
    while (i < 4){
      if (dir == i){
	int		rez;
	if ((rez = (this->*playerptr[i])(cx, cy, placed, count, startx, starty, temp, maxx, maxy)))
	  return (rez);
	break;
      }
      ++i;
    }
  }
  return (-1);
}

void		Content::putPlayer(int nb, std::vector<std::vector<Types> > &temp, int tot)
{
  int		ax = 0;
  int		ay = 0;
  int		placed = 0;
  int		fcuk = 0;

  while (placed != nb && fcuk != tot)
    {
      ax = 0;
      ay = 0;
      while (temp[ax][ay] != 0 && fcuk != tot){
	ax = rand.getRand(0, this->x * 2 + 1);
	ay = rand.getRand(0, this->y * 2 + 1);
	++fcuk;
      }
      if (fcuk != tot)
	this->getSpawn(temp, this->x * 2 + 1, this->y * 2 + 1, ax, ay, placed);
      else
	throw ExceptMap("Map Conflict");
    }
}
