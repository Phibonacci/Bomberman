/**
 * @file BombType.hh
 */
#ifndef BOMBTYPE_HH_
# define BOMBTYPE_HH_

# include "AComponent.hh"
# include <istream>

/**
 * @class BombType
 * @brief class of the bomb {AbstractClass}
 */
class		BombType : public AComponent
{
public:
  /**
   * @fn BombType
   * @brief constructor
   */
  BombType(){};
  /**
   * @fn BombType
   * @brief destructor
   */
  virtual ~BombType(){};

  /**
   * @var BTYPE
   * @brief enum of the different bomb type
   */
  enum		BTYPE
  {
    NORMAL,
    PIERCE,
  };
};

/**
 * @class Pierce
 * @brief class of the bomb
 */
class		Pierce : public BombType
{
private:
  /**
   * @var canPierce
   * @brief bool : true if the bomb can pierce wall
   */
  bool	canPierce;

public:
  /**
   * @fn Pierce
   * @brief constructor
   */
  Pierce() { canPierce = true; }
  /**
   * @fn Pierce
   * @brief constructor for the loadgame
   */
  Pierce(std::istream & is) { is >> canPierce; }
  /**
   * @fn Pierce
   * @brief destructor
   */
  virtual ~Pierce(){};
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream & os) const;
  /**
   * @fn getPierce
   * @brief check if the bomb can pierce the wall
   */
  bool		getPierce()
  {
    return (canPierce);
  }
};

#endif
