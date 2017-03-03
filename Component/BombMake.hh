/**
 * @file BombMake.hh
 */
#ifndef BOMBMAKE_H_
# define BOMBMAKE_H_

# include "AComponent.hh"
# include "Player.hh"
# include <istream>
/**
 * @class BombMake
 * @brief Component that allows Entity to make Bomb
 */
class	BombMake : public AComponent
{
private:
  /**
   ** @brief For bomb setting verification
   */
  class	TryPutBomb
  {
    bool	_canPutBomb;
  public:
    /**
     ** Basic constructor for TryPutBomb
     */
    TryPutBomb() : _canPutBomb(true) {}

    /**
     ** Trys to set a bomb
     */
    void	operator()(Entity *);

    /**
     ** verify if a bomb can be set
     */
    bool	isOk() const {return _canPutBomb;}
  };
public:

  /**
   ** Basic constructor
   */
  BombMake() {}

  /**
   ** Constructor with a name
   */
  BombMake(std::istream &) {}
 
  /**
   ** This function creates a bomb
   */
  void	makeBomb();
  
  /**
   ** This function creates a bomb and add it to the player
   */
  void	makeBomb(Player *player);
  virtual ~BombMake() {}

  /**
   ** This function saves the bomb in the serializer
   */
  virtual void	saveSelf(std::ostream& os) const;
};

/**
 * @class BombMaker
 * @brief Component that allows Entity to make himself bomb
 */
class	BombMaker : public AUpdateComponent
{
private:
  float	_coolDown;
public:
  /**
   ** Basic Constructor
   */
  BombMaker() : _coolDown(0) {}

  /**
   ** Basic Constructor
   */
  BombMaker(std::istream & is) { is >> _coolDown;}

  /**
   ** This function updates the bomb exploding time
   */
  virtual void		update(gdl::Clock const &clock, gdl::Input &input);
  virtual ~BombMaker() {}
  
  /**
   ** This functions saves the exploding bomb in the serializer
   */
  virtual void	saveSelf(std::ostream&) const;
};

#endif /* !BOMBMAKE_H_ */

