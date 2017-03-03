/**
 * @file HasBonus.hh
 */
#ifndef HASBONUS_H_
# define HASBONUS_H_

# include "Destruction.hh"

class	Entity;

/**
 * @class HasBonus
 * @brief component who detect if the entity has a bonus (ex : wall)
 */
class	HasBonus : public ADestruction
{
private:
  /**
   * @var _bonus
   * @brief the bonus
   */
  Entity	*_bonus;
public:
  /**
   * @brief constructor
   */
  HasBonus(Entity *bonus) : _bonus(bonus) {}
  /**
   * @brief constructor for the load game
   */
  HasBonus(std::istream &);
  /**
   * @fn destroy
   * @brief destroy it
   */
  virtual void	destroy();
  /**
   * @fn ~HasBonus
   * @brief destructor
   */
  virtual ~HasBonus();
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream & os) const;

};

#endif /* !HASBONUS_H_ */
