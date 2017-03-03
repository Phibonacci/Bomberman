#include <iostream>
#include <string>
#include <vector>

#include "Case.hh"

Case::Case(const int &cx, const int &cy)
{
  int		i = 0;

  this->x = cx;
  this->y = cy;
  while (i < 4)
    {
      this->Walls[i] = false;
      ++i;
    }
  this->beenVisited = Case::NO;
  this->isWhat = Case::FREE;
}

Case::~Case()
{

}

Case::Case()
{
  int  	i = 0;

  this->x = 0;
  this->y = 0;
  while (i < 4)
    {
      this->Walls[i] = false;
      ++i;
    }
  this->beenVisited = Case::NO;
  this->isWhat = Case::FREE;
}

Case&		Case::operator=(const Case & old)
{
  Case		*tmp = new Case;

  tmp->beenVisited = Case::NO;
  tmp->isWhat = FREE;
  tmp->setX(old.getX());
  tmp->setY(old.getY());
  return (*tmp);
}

int		Case::getX() const
{
  return (this->x);
}

int		Case::getY() const
{
  return (this->y);
}

void		Case::setX(const int &cx)
{
  this->x = cx;
}

void		Case::setY(const int &cy)
{
  this->y = cy;
}

void		Case::setWall(const DirWall &type, const bool st)
{
  this->beenVisited = Case::YES;
  this->Walls[type] = st;
}

Case::Verb	Case::getVisited() const
{
  return(this->beenVisited);
}

void		Case::setVisit(Case::Verb wut)
{
  this->beenVisited = wut;
}

Case::Type	Case::getType()
{
  return (this->isWhat);
}

void	     	Case::getWall(bool *tab)
{
  tab[0] = false;
  tab[1] = false;
  tab[2] = false;
  tab[3] = false;
  if (this->Walls[0] == true)
    tab[0] = true;
  if (this->Walls[1] == true)
    tab[1] = true;
  if (this->Walls[2] == true)
    tab[2] = true;
  if (this->Walls[3] == true)
    tab[3] = true;
}

void		Case::setType(Case::Type t)
{
  this->isWhat = t;
}
