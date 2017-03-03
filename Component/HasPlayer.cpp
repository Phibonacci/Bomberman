#include "HasPlayer.hh"
#include "SaveLoad.hh"
#include "GameEngine.hh"

HasPlayer::HasPlayer(std::istream &is)
  : _player(NULL)
{
  GameParty const	*current;
  int			playeridx;

  is >> playeridx >> _attach;
  if ((current = SaveLoad::getCurrent()))
    {
      _player = current->getPlayer(playeridx);
    }
}

HasPlayer::~HasPlayer()
{
  if (_attach && _player)
    {
      _player->getPerson() = 0;
      GameEngine::_sound.zPlay(Zik::PLAYEROUT);
    }
}

void HasPlayer::setOwner(Entity *owner)
{
  _owner = owner;
  if (_attach)
    {
      if (_player)
	_player->getPerson() = _owner;
    }
}

void	HasPlayer::saveSelf(std::ostream& os) const
{
  int	playeridx;
  GameParty const	*current;

  if ((current = SaveLoad::getCurrent()))
    {
      playeridx = current->getPlayerIdx(_player);
      os << "HasPlayer" << " " << playeridx
	 << " " << _attach << std::endl;
    }
}
