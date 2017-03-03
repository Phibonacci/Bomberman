#include "Content.hh"

void				Content::goUp(int &x, int &y)
{
  this->all[x][y].setWall(Case::UP, true);
  --x;
  this->all[x][y].setWall(Case::DOWN, true);
}

void				Content::goRight(int &x, int &y)
{
  this->all[x][y].setWall(Case::RIGHT, true);
  ++y;
  this->all[x][y].setWall(Case::LEFT, true);
}

void				Content::goDown(int &x, int &y)
{
  this->all[x][y].setWall(Case::DOWN, true);
  ++x;
  this->all[x][y].setWall(Case::UP, true);
}

void				Content::goLeft(int &x, int &y)
{
  this->all[x][y].setWall(Case::LEFT, true);
  --y;
  this->all[x][y].setWall(Case::RIGHT, true);
}

int		Content::checkUp(std::vector<std::vector<Types> > &temp, int i, int j)
{
  if (temp[i - 1][j] == WALL)
    return (1);
  return (0);
}

int		Content::checkRight(std::vector<std::vector<Types> > &temp, int i, int j)
{
  if (temp[i][j + 1] == WALL)
    return (1);
  return (0);
}

int		Content::checkDown(std::vector<std::vector<Types> > &temp, int i, int j)
{
  if (temp[i + 1][j] == WALL)
    return (1);
  return (0);
}

int		Content::checkLeft(std::vector<std::vector<Types> > &temp, int i, int j)
{
  if (temp[i][j - 1] == WALL)
    return (1);
  return (0);
}



void		Content::removeUp(std::vector<std::vector<Types> > &temp, int i, int j)
{
  temp[i - 1][j] = BREAK;
}

void		Content::removeRight(std::vector<std::vector<Types> > &temp, int i, int j)
{
  temp[i][j + 1] = BREAK;
}

void		Content::removeDown(std::vector<std::vector<Types> > &temp, int i, int j)
{
  temp[i + 1][j] = BREAK;
}

void		Content::removeLeft(std::vector<std::vector<Types> > &temp, int i, int j)
{
  temp[i][j - 1] = BREAK;
}

bool		Content::isFreeAround(std::vector<std::vector<Types> > &temp, int i, int j)
{
  int		c = 0;
  int		t = 0;
  int		dir;

  while (c < 4)
    {
      t += (this->*checkPtr[c])(temp, i, j);
      ++c;
    }
  if (t == 4)
    {
      dir = this->rand.getRand(1, 4);
      (this->*removePtr[dir])(temp, i, j);
    }
  return (false);
}

int				Content::dirPlayerUp(int &cx, int &cy, int &placed, int &count,
						     int &startx, int &starty, std::vector<std::vector<Types> > &temp,
						     int &maxx, int &maxy)
{
  --cx;
  ++count;
  temp[startx][starty] = RESERVED;
  if (1 == this->getSpawn(temp, maxx, maxy, cx, cy, placed))
    return (1);
  temp[startx][starty] = FREE;
  --count;
  ++cx;
  return (0);
}

int				Content::dirPlayerRight(int &cx, int &cy, int &placed, int &count,
							int &startx, int &starty, std::vector<std::vector<Types> > &temp,
							int &maxx, int &maxy)
{
  ++cy;
  ++count;
  temp[startx][starty] = RESERVED;
  if (1 == this->getSpawn(temp, maxx, maxy, cx, cy, placed))
    return (1);
  temp[startx][starty] = FREE;
  --count;
  --cy;
  return (0);
}

int				Content::dirPlayerDown(int &cx, int &cy, int &placed, int &count,
						       int &startx, int &starty, std::vector<std::vector<Types> > &temp,
						       int &maxx, int &maxy)
{
  ++cx;
  ++count;
  temp[startx][starty] = RESERVED;
  if (1 == this->getSpawn(temp, maxx, maxy, cx, cy, placed))
    return (1);
  temp[startx][starty] = FREE;
  --count;
  --cx;
  return (0);
}

int				Content::dirPlayerLeft(int &cx, int &cy, int &placed, int &count,
						       int &startx, int &starty, std::vector<std::vector<Types> > &temp,
						       int &maxx, int &maxy)
{
  --cy;
  ++count;
  temp[startx][starty] = RESERVED;
  if (1 == this->getSpawn(temp, maxx, maxy, cx, cy, placed))
    return (1);
  temp[startx][starty] = FREE;
  --count;
  ++cy;
  return (0);
}

void		Content::getDirSpawn(int maxx, int maxy, std::vector<Case::DirWall> &lili,
				     std::vector<std::vector<Types> > &tab, int cx, int cy) const
{
  if (cx + 1 < maxx){
    if (tab[cx + 1][cy] == 0)
      lili.push_back(Case::DOWN);
  }
  if (cx - 1 >= 0){
    if (tab[cx - 1][cy] == 0)
      lili.push_back(Case::UP);
  }
  if (cy + 1 < maxy){
    if (tab[cx][cy + 1] == 0)
      lili.push_back(Case::RIGHT);
  }
  if (cy - 1 >= 0){
    if (tab[cx][cy - 1] == 0)
      lili.push_back(Case::LEFT);
  }
}
