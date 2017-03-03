#include "SaveLoad.hh"
#include <fstream>
#include "Except.hpp"
#include "Entity.hpp"
#include "Time.hpp"

GameParty *SaveLoad::current_save = NULL;

void SaveLoad::saveVec3(std::ostream &os, glm::vec3 const& vec)
{
  os << vec.x << " " << vec.y << " " << vec.z;
}

void SaveLoad::loadVec3(std::istream &os, glm::vec3 & vec)
{
  os >> vec.x >> vec.y >> vec.z;
}

void	SaveLoad::loadBoard(Board *&board, std::ifstream &ifs)
{
  int	x;
  int	y;

  ifs >> x >> y;
  board = new Board(x, y);
  current_save->setBoard(board);
  while (!ifs.eof())
    {
      std::string	begin;

      ifs >> begin;
      if (begin == "<Entity")
	{
	  Entity	*rt = new Entity(ifs);
	  board->addEntity(rt);
	}
      if (begin == "Board>")
	break ;
    }
}

void	SaveLoad::loadParty(std::string const& file)
{
  std::ifstream ifs(file.c_str(), std::ifstream::in);
  if (ifs.is_open() == false)
    throw BombermanException("Cant find save " + file);
  while (!ifs.eof())
    {
      std::string	begin;

      ifs >> begin;
      if (begin == "<GamePlayer")
	{
	  GamePlayer	*pl = new GamePlayer(ifs);

	  current_save->setGamePlayer(pl);
	}
      if (begin == "<Board")
	{
	  Board	*board;

	  loadBoard(board, ifs);
	}
    }
}

void	SaveLoad::saveParty()
{
  std::string	str;
  std::string::iterator it;

  str = std::string(".saves/") + CTime::Time::getCurrentTime();
  it = str.begin();
  while (it != str.end())
    {
      if (*it == ' ')
       *it = '_';
      if (*it == '\n')
	*it = '_';
      ++it;
    }
  str += std::string(".save");
  saveParty(str);
}

void	SaveLoad::saveParty(std::string const& file)
{
  std::ofstream	ofs(file.c_str(), std::ofstream::out);

  current_save->saveSelf(ofs);
  ofs.close();
}

SaveLoad::SaveLoad(GameParty *g)
{
  if (current_save)
    throw BombermanException("Can not save at the time");
  current_save = g;
}

GameParty const	*SaveLoad::getCurrent()
{
  return current_save;
}

SaveLoad::~SaveLoad()
{
  current_save = NULL;
}
