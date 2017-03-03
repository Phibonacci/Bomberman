/**
 * @file OnTouch.hh
 */
#ifndef ONTOUCH_H_
# define ONTOUCH_H_

# include "AComponent.hh"

/**
 * @class OnTouch
 * @brief Component Touch {Abstract class}
 */
class	OnTouch : public AComponent
{
public:
  /**
   * @fn OnTouch
   * @brief constructor
   */
  OnTouch() {}
  /**
   * @fn canBeTouch
   * @brief check if the target is touch
   */
  virtual bool		canBeTouch(Entity const&) const = 0;
  /**
   * @fn getTouchBy
   * @brief check if this is touch by the target
   */
  virtual bool		getTouchBy(Entity &) = 0;
  /**
   * @fn ~OnTouch
   * @brief destructor
   */
  virtual ~OnTouch() {}
};

/**
 * @class OnTouchBlock
 * @brief Component Touch for block
 */
class	OnTouchBlock : public OnTouch
{
public:
  /**
   * @fn OnTouchBlock
   * @brief constructor
   */
  OnTouchBlock() {}
  /**
   * @fn OnTouchBlock
   * @brief constructor for load the data {loadgame}
   */
  OnTouchBlock(std::istream &) {}
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
   * @brief this function save the data {savegame}
   */
  virtual void	saveSelf(std::ostream&) const;
  /**
   * @fn ~OnTouchBlock
   * @brief destructor
   */
  virtual ~OnTouchBlock() {}
};

/**
 * @class OnTouchCollect
 * @brief Component Touch for bonus
 */
class	OnTouchCollect : public OnTouch
{
public:
  /**
   * @fn OnTouchCollect
   * @brief Constructor
   */
  OnTouchCollect() {}
  /**
   * @fn canBeTouch
   * @brief check if the target is touch
   */
  virtual bool		canBeTouch(Entity const&) const;
  /**
   * @fn getTouchBy
   * @brief check if this is touch by the target
   */
  virtual bool		getTouchBy(Entity &) = 0;
  /**
   * @fn ~OnTouchCollect
   * @brief destructor
   */
  virtual ~OnTouchCollect() {}
};

/**
 * @class OnTouchFire
 * @brief Component Touch for bomb fire
 */
class	OnTouchFire : public OnTouch
{
public:
  /**
   * @fn OnTouchFire
   * @brief constructor
   */
  OnTouchFire() {}
  /**
   * @fn OnTouchFire
   * @brief constructor for load the data {loadgame}
   */
  OnTouchFire(std::istream &) {}
  /**
   * @fn canBeTouch
   * @brief check if the target is touch
   */
  virtual bool		canBeTouch(Entity const&) const {return true;}
  /**
   * @fn getTouchBy
   * @brief check if this is touch by the target
   */
  virtual bool		getTouchBy(Entity &target);
  /**
   * @fn saveSelf
   * @brief this function save the data {savegame}
   */
  virtual void	saveSelf(std::ostream&) const;
  /**
   * @fn ~OnTouchFire
   * @brief destructor
   */
  virtual ~OnTouchFire() {}
};

#endif /* !ONTOUCH_H_ */
