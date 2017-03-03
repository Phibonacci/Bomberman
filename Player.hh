/**
 * @file Player.hh
 */
#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "Peripheral.hh"
# include "BombType.hh"
# include "maRand.hh"
# include <iostream>

class	Entity;

/**
 * @class Player
 * @brief the player
 */
class	Player
{
protected:
  /**
   * @var _bombCount
   * @brief stock of the bomb
   */
  int		_bombCount;
  /**
   * @var _bombRange
   * @brief power of the bomb
   */
  int		_bombRange;
  /**
   * @var _score
   * @brief score collected by player
   */
  int		_score;
  /**
   * @var _speed
   * @brief speed of the player
   */
  float		_speed;
  Controller::IControl	*_control;
  Entity	*_controlling;
  /**
   * @var _bombType
   * @brief player can drop this kind of bomb
   */
  BombType::BTYPE	_bombType;
  gdl::BasicShader	_shader;
  /**
   * @var _color
   * @brief color of the "PON PON"
   */
  glm::vec4		_color;

public:
  /**
   * @fn Player
   * @brief basic constructor
   */
  Player(bool isPlayer);
  void			load(std::istream &is);
  void			setControl(Controller::IControl *control) {_control = control;}
  Controller::IControl	*getControl() const {return _control;}
  /**
   * @fn getBombType
   * @brief return the current bomb use by the player
   */
  BombType::BTYPE	getBombType() const {return _bombType;}
  /**
   * @fn setBombType
   * @brief set the new BombType for this player
   */
  void			setBombType(BombType::BTYPE newBomb) { _bombType = newBomb;}

  /**
   * @fn saveSelf
   * @brief save the data when the user save the game
   */
  void	saveSelf(std::ostream &os) const;

  /**
   * @fn getBombCount
   * @brief return the number of bomb in stock (return REFERENCE)
   */
  int	&getBombCount() {return _bombCount;}

  /**
   * @fn getBombCount
   * @brief return the number of bomb in stock
   */
  int	getBombCount() const {return _bombCount;}

  /**
   * @fn getBombRange
   * @brief return the range of the bomb (return REFERENCE)
   */
  int	&getBombRange() {return _bombRange;}

  /**
   * @fn getBombRange
   * @brief return the range of the bomb
   */
  int	getBombRange() const {return _bombRange;}

  /**
   * @fn setBombRange
   * @brief set the range of the bomb at 6 (6 is the max)
   */
  void	setBombRange() { _bombRange = 6;}

  /**
   * @fn getScore
   * @brief return the score collected (return REFERENCE)
   */
  int	&getScore() {return _score;}

  /**
   * @fn getScore
   * @brief return the score collected
   */
  int	getScore() const {return _score;}

  /**
   * @fn getSpeed
   * @brief return the speed of this player (return REFERENCE)
   */
  float	&getSpeed() {return _speed;}

  /**
   * @fn getSpeed
   * @brief return the speed of this player
   */
  float	getSpeed() const {return _speed;}

  Entity	*getPerson() const {return _controlling;}
  Entity	*&getPerson() {return _controlling;}
  bool		isUser() const;
  gdl::AShader	&getShader() {return (_shader);};

  /**
   * @fn getColor
   * @brief return the color of the "PON PON"
   */
  glm::vec4	&getColor() {return (_color);};
  ~Player() {}
};

#endif /* !PLAYER_HH_ */
