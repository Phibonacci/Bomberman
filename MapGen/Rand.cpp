#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "maRand.hh"

maRand::maRand()
{

}

maRand::~maRand()
{

}

void		maRand::setSeed(int _seed)
{
  this->seed = _seed;
}

void		maRand::initSeed()
{
  srand(this->seed);
}

int		maRand::getRand(int x, int y) const
{
  int		r;

  r = rand() % y + x;
  return (r);
}

int		maRand::getPid() const
{
  return (getpid());
}
