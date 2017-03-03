/**
 * @file Teleport.hh
 */
#ifndef TELEPORT_HH_
# define TELEPORT_HH_

# include "AComponent.hh"
# include "OnTouch.hh"
# include "Position.hh"

/**
 * @class Teleport
 * @brief Component for the teleporter
 */
class	Teleport : public OnTouch
{
private:
  /**
   * @var getLocation
   * @brief position of the teleport
   */
  Position		*getLocation() const;
public:
  /**
   * @fn Teleport
   * @brief the constructor
   */
  Teleport();
  /**
   * @fn Teleport
   * @brief the constructor for load the data
   */
  Teleport(std::istream &);
  /**
   * @fn canBeTouch
   * @brief check if the target is touch
   */
  virtual bool		canBeTouch(Entity const&) const;
  /**
   * @fn getTouchBy
   * @brief check if this is touch by the target
   */
  virtual bool		getTouchBy(Entity &);
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream&) const;
  /**
   * @fn ~Teleport
   * @brief destructor
   */
  virtual ~Teleport();
};

/**
 * @class BeforeTp
 * @brief tp on the block
 */
class	BeforeTp : public AComponent
{
public:
  /**
   * @fn BeforeTp
   * @brief constructor
   */
  BeforeTp(){}
  /**
   * @fn ~BeforeTp
   * @brief destructor
   */
  ~BeforeTp(){}
  /**
   * @fn BeforeTp
   * @brief constructor for load the game
   */
  BeforeTp(std::istream &){}
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream& os) const {os << "BeforeTp" << std::endl;}
};

#endif
