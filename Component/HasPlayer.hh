#ifndef HASPLAYER_H_
# define HASPLAYER_H_

# include "AComponent.hh"
# include "Player.hh"

/**
 * @brief the player Entity
 */
class	HasPlayer : public AComponent
{
  /**
   * @brief the player
   */
  Player	*_player;

  /**
   * @brief if a player is attached
   */
  bool		_attach;
public:
  /**
   * @brief the basic contructor
   */
  HasPlayer(Player *pl, bool atch = false) : _player(pl), _attach(atch) {}

  /**
   * @brief the load contructor
   */
  HasPlayer(std::istream & );

  /**
   * @param owner
   * @brief set the @a _player with the @a onwer
   */
  virtual void	setOwner(Entity *owner);

  /**
   * @return @a _player
   * @brief return the onwer
   */
  Player	*getPlayer() const {return _player;}

  /**
   * @return @a _player
   * @brief return the onwer
   */
  Player	*&getPlayer() {return _player;}

  /**
   * @brief the destructor
   */
  virtual ~HasPlayer();

  /**
   * @brief save the class
   */
  virtual void	saveSelf(std::ostream&) const;
};

#endif /* !HASPLAYER_H_ */
