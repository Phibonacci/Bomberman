#include <stdexcept>
#include "GamePlayer.hh"
#include "MasterController.hpp"
#include "Except.hpp"

GamePlayer::GamePlayer(unsigned int player, unsigned int ai)
  : _players(player, NULL), _nplayers(player), _iAcount(ai)
{
  unsigned int i;

  for (i = 0 ; i < player - ai; i++)
    _players[i] = new Player(true);
  while (i < player)
    {
      _players[i] = new Player(false);
      i++;
    }
}

GamePlayer::GamePlayer(std::istream& is)
{
  is >> _nplayers >> _iAcount;
  _players.resize(_nplayers);
  unsigned int i;
  for (i = 0; i < _nplayers ; i++)
    {
      _players[i] = new Player(true);
      std::string	str;
      is >> str;
      if (str != "Player" || is.eof() == true)
	throw BombermanException("file corrupted !");
      _players[i]->load(is);
    }
  std::string	str;
  is >> str;

  if (str != "GamePlayer>")
    throw BombermanException("file corrupted !");
}

void	GamePlayer::saveSelf(std::ostream& os) const
{
  os << _nplayers << " " << _iAcount << std::endl;
  for (unsigned int i = 0 ; i < _nplayers ; i++)
    _players[i]->saveSelf(os);
}

Player	*GamePlayer::getPlayer(unsigned int index) const
{
  return (_players[index % _nplayers]);
}

Player	*&GamePlayer::getPlayer(unsigned int index)
{
  return (_players[index % _nplayers]);
}

GamePlayer::~GamePlayer()
{
  while (!_players.empty())
    {
      Player* p = _players.back();
      delete p;
      _players.pop_back();
    }
  Controller::MasterController::restart();
}
