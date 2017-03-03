/**
 * @file Bonus.hh
 */
#ifndef __BONUS_HH__
# define __BONUS_HH__

# include "OnTouch.hh"
# include <istream>

/**
 * @class SpeedModify
 * @brief this bonus modify the speed of the target
 */
class SpeedModify : public OnTouchCollect
{
  /**
   * @var _modify
   * @brief the variable set for modify the speed when the bonus is take
   */
  float	_modify;

public:
  /**
   * @brief the basic constructor
   */
  SpeedModify(float modify) : _modify(modify) {}
  /**
   * @brief the constructor for load the data
   */
  SpeedModify(std::istream & is) { is >> _modify; }
  /**
   * @fn ~SpeedModify
   * @brief the destructor
   */
  virtual ~SpeedModify() {}
  /**
   * @fn getTouchBy
   * @brief when the bonus is take
   */
  virtual bool	getTouchBy(Entity &);
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream&) const;
};

/**
 * @class RangeBombModify
 * @brief this bonus modify the range of the bomb
 */
class RangeBombModify : public OnTouchCollect
{
  /**
   * @var _modify
   * @brief the variable set for modify the speed when the bonus is take
   */
  int	_modify;

public:
  /**
   * @brief the basic constructor
   */
  RangeBombModify(int modify) : _modify(modify) {}

  /**
   * @brief the constructor for save the data when the game is save
   */
  RangeBombModify(std::istream & is) { is >> _modify; }

  /**
   * @fn ~RangeBombModify
   * @brief the basic destructor
   */
  virtual ~RangeBombModify() {}

  /**
   * @fn getTouchBy
   * @brief when the bonus is take
   */
  virtual bool	getTouchBy(Entity &);
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream&) const;
};

/**
 * @class NumBombModify
 * @brief this bonus modify the number of the bomb in the stock
 */
class NumBombModify : public OnTouchCollect
{
  /**
   * @var _modify
   * @brief the variable set for modify the speed when the bonus is take
   */
  int	_modify;

public:
  /**
   * @brief the basic constructor
   */
  NumBombModify(int modify) : _modify(modify) {}
  /**
   * @brief the constructor for save the data when the game is save
   */
  NumBombModify(std::istream & is) { is >> _modify; }
  /**
   * @fn ~NumBombModify
   * @brief the basic destructor
   */
  virtual ~NumBombModify() {}

  /**
   * @fn getTouchBy
   * @brief when the bonus is take
   */
  virtual bool	getTouchBy(Entity &);
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream&) const;
};

/**
 * @class Skull
 * @brief this bonus destroy all the bonus of the player
 */
class Skull : public OnTouchCollect
{
  /**
   * @var _modify
   * @brief the variable set for modify the speed when the bonus is take
   */
  int	_modify;

public:
  /**
   * @brief the basic constructor
   */
  Skull(int modify) : _modify(modify) {}
  /**
   * @brief the constructor for save the data when the game is save
   */
  Skull(std::istream & is) { is >> _modify; }
  /**
   * @fn ~Skull
   * @brief the basic destructor
   */
  virtual ~Skull() {}

  /**
   * @fn getTouchBy
   * @brief when the bonus is take
   */
  virtual bool	getTouchBy(Entity &);
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream&) const;
};

/**
 * @class KickShoe
 * @brief the player can kick the bomb
 */
class KickShoe : public OnTouchCollect
{
public:
  /**
   * @brief the basic constructor
   */
  KickShoe() {}
  /**
   * @brief the constructor for save the data when the game is save
   */
  KickShoe(std::istream &) {}
  /**
   * @fn ~KickShoe
   * @brief the basic destructor
   */
  virtual ~KickShoe() {}

  /**
   * @fn getTouchBy
   * @brief when the bonus is take
   */
  virtual bool	getTouchBy(Entity &);
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream&) const;
};

#endif	/* __BONUS_HH__*/
