#include <iostream>

#include "Case.hh"
#include "Content.hh"
#include "maRand.hh"

Content::Content(int _x, int _y)
  : x(_x), y(_y),
    all(_x, std::vector<Case>(_y, Case()))
{
  rand.setSeed(time(NULL) * rand.getPid() / (x + y + 1));
  rand.initSeed();

  ptr[0] = &Content::goUp;
  ptr[1] = &Content::goRight;
  ptr[2] = &Content::goDown;
  ptr[3] = &Content::goLeft;

  playerptr[0] = &Content::dirPlayerUp;
  playerptr[1] = &Content::dirPlayerRight;
  playerptr[2] = &Content::dirPlayerDown;
  playerptr[3] = &Content::dirPlayerLeft;

  checkPtr[0] = &Content::checkUp;
  checkPtr[1] = &Content::checkRight;
  checkPtr[2] = &Content::checkDown;
  checkPtr[3] = &Content::checkLeft;

  removePtr[0] = &Content::removeUp;
  removePtr[1] = &Content::removeRight;
  removePtr[2] = &Content::removeDown;
  removePtr[3] = &Content::removeLeft;
}

Content::~Content()
{

}

bool		Content::isOk(int x, int y) const
{
  if (x <= this->x && y <= this->y)
    return (true);
  return (false);
}

int		Content::getX() const
{
  return (this->x);
}

int		Content::getY() const
{
  return (this->y);
}

void		Content::getDir(int Cx, int Cy, std::vector<Case::DirWall> &lili, Case::Verb T) const
{
  int		a;
  int		b;
  int		c;
  int		d;

  a = (Cx + 1);
  b = (Cy + 1);
  c = (Cx - 1);
  d = (Cy - 1);

  if (a < this->x){
      if (this->all[a][Cy].getVisited() == T)
	lili.push_back(Case::DOWN);
    }
  if (c >= 0){
      if (this->all[c][Cy].getVisited() == T)
	lili.push_back(Case::UP);
    }
  if (b < this->y){
      if (this->all[Cx][b].getVisited() == T)
	lili.push_back(Case::RIGHT);
    }
  if (d >= 0){
      if(this->all[Cx][d].getVisited() == T)
	lili.push_back(Case::LEFT);
    }
}

int				Content::core(int &Cx, int &Cy)
{
  int				dir;
  int				i = 0;
  int				save;

  dto.clear();
  save = 0;
  this->getDir(Cx, Cy, dto, Case::NO);
  this->all[Cx][Cy].setVisit(Case::YES);
  if (dto.size() > 0){
      dir = rand.getRand(0, dto.size());
      dir = dto[dir];
      if (dto.size() > 1){
	  int		tab[2] = {Cx, Cy};
	  this->mastack.push(tab);
	}
      i = 0;
      while (i < 4)
      	{
      	  if (dir == i)
	    (this->*ptr[i])(Cx, Cy);
      	  ++i;
      	}
      save = 0;
    }
  else{
      if (this->mastack.size() == 0)
	save = 1;
      else{
	  int *temp = mastack.top();
	  this->mastack.pop();
	  save = 0;
	  Cx = temp[0];
	  Cy = temp[1];
	}
    }
  if (save)
    return (1);
  return (0);
}

void		Content::ifPlace(bool dto[4], std::vector<std::vector<Types> > &temp, int i, int j)
{
  if (!dto[0] == true)
    temp[i - 1][j] = WALL;
  if (!dto[1] == true)
    temp[i][j + 1] = WALL;
  if (!dto[2] == true)
    temp[i + 1][j] = WALL;
  if (!dto[3] == true)
    temp[i][j - 1] = WALL;
}

void		Content::Convert(std::vector<std::vector<Types> > &temp, int gendra)
{
  int					i = 0, j = 0, ax = 0, ay = 0;
  bool					dto[4];

  while (j < (this->y * 2 + 1))
    temp[i][j++] = INDE;
  ++i;
  while (i < ((this->x * 2)))
    {
      j = 0;
      ay = 0;
      if (i % 2 != 0)
	{
	  while (j < (this->y * 2) && ay != this->y)
	    {
	      if (j % 2 != 0)
		{
		  all[ax][ay].getWall(dto);
		  ifPlace(dto, temp, i, j);
		  ++ay;
		}
	      else
		temp[i][j] = FREE;
	      ++j;
	    }
	  ++ax;
	}
      else
	{
	  j = 0;
	  while (j < ((this->y * 2) + 1))
	    {
	      if (j == 0 || j + 1 == (this->y * 2 + 1))
		temp[i][j] = INDE;
	      if (gendra == 0 && (j == 0 || (j + 1 == (this->y * 2 + 1)) || j % 2 == 0))
		temp[i][j] = WALL;
	      else if (gendra == 1 && (j == 0 || (j + 1 == (this->y * 2 + 1))))
		temp[i][j] = WALL;
	      else
		temp[i][j] = FREE;
	      ++j;
	    }
	}
      ++i;
    }
  endConvert(temp);
}

void		Content::endConvert(std::vector<std::vector<Types> > &temp)
{
  int		i = 0;
  int		j;

  while (i < (this->x * 2 + 1))
    {
      j = 0;
      while (j < this->y * 2 + 1)
	{
	  if (i == 0 || j == 0 || j == (this->y * 2) || i == (this->x * 2))
	    temp[i][j] = INDE;
	  ++j;
	}
      i++;
    }
}

void		Content::Finalyze(std::vector<std::vector<Types> > &temp, int ratioFree, int ratioUnbreak)
{
  int		i = 1;
  int		j = 1;
  int		switsh = 0;

  while (i < this->x * 2)
    {
      j = 1;
      while (j < this->y * 2)
	{
	  if (temp[i][j] == 0)
	    {
	      if (temp[i][j] != INDE && (switsh = this->rand.getRand(1, 10)) > (ratioFree / 10))
		temp[i][j] = BREAK;
	      else
		temp[i][j] = FREE;
	    }
	  else if (temp[i][j] == 1 || temp[i][j] == 8)
	    {
	      if (temp[i][j] != INDE
		  && (this->rand.getRand(1, 10)) > (ratioUnbreak / 10))
		{
		  if (this->rand.getRand(1, 10) > (ratioFree / 10))
		      temp[i][j] = BREAK;
		  else
		    temp[i][j] = FREE;
		}
	    }
	  isFreeAround(temp, i, j);
	  ++j;
	}
      ++i;
    }
}
