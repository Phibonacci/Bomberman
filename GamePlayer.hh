#ifndef GAMEPLAYER_H_
# define GAMEPLAYER_H_

# include "Player.hh"
# include <vector>

/**
 * @brief manage players
 */
class			GamePlayer
{
  /**
   * @brief the players vector
   */
  std::vector<Player*>	_players;

  /**
   * @brief total player number
   * @note player + ai
   */
  unsigned int		_nplayers;

  /**
   * @brief ai number
   */
  unsigned int		_iAcount;
public:
  /**
   * @param players the player number
   * @param ai the ai number
   * @brief the default contructor
   */
  GamePlayer(unsigned int players, unsigned int ai);

  /**
   * @param is containt the variables to load
   * @brief the load contructor
   */
  GamePlayer(std::istream& is);

  /**
   * @param os where put variables to save it
   * @brief save the class
   */
  void		saveSelf(std::ostream& os) const;

  /**
   * @return @a GamePlayer::_nplayers
   * @brief return the total player number
   */
  unsigned int	getPlayerCount() const {return _nplayers;}

  /**
   * @return @a GamePlayer::_iAcount
   * @brief return the ai number
   */
  unsigned int	getIACount() const {return _iAcount;}

  /**
   * @return @a GamePlayer::_iAcount
   * @brief return the ai number
   */
  unsigned int	&getIACount() {return _iAcount;}

  /**
   * @return @a GamePlayer::_nplayers - @a GamePlayer::_iAcount
   * @brief return the player number
   */
  unsigned int	getUserCount() const {return _nplayers - _iAcount;}

  /**
   * @param index the player to return
   * @return the player corresponding to the index
   * @brief return the player corresponding to the index
   */
  Player	*getPlayer(unsigned int index) const;

  /**
   * @param index the player to return
   * @return the player corresponding to the index
   * @brief return the player corresponding to the index
   */
  Player	*&getPlayer(unsigned int index);

  /**
   * @brief the basic destructor
   */
  ~GamePlayer();
};

#endif /* !GAMEPLAYER_H_ */
