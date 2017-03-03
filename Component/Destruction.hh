/**
 * @file Destruction.hh
 */
#ifndef DESTRUCTION_HH_
# define DESTRUCTION_HH_

# include "AComponent.hh"
# include "Position.hh"
# include "Hitbox.hh"
# include <string>

/**
 * @class ADestruction
 * @brief destruction interface
 */
class	ADestruction : public AComponent
{
public:
  /**
   * @fn destroy
   * @brief function for the ... destruction
   */
  virtual void	destroy() = 0;
  /**
   * @brief Destructor
   */
  virtual ~ADestruction() {}
};

/**
 * @class BombExplode
 * @brief when a bomb explode
 */
class	BombExplode : public ADestruction
{
 private:
  /**
   * @brief the bomb range
   */
  unsigned int	_range;
 private:
  /**
   * @brief try to destroy objects
   */
  class		TryDestruct
  {
    /**
     * @brief the entity to try to destroy
     */
    Entity	*_self;

    /**
     * @brief if the entity can be destroy
     */
    bool	_canDestruct;
  public:
    /**
     * @brief a basic contructor
     */
  TryDestruct(Entity *by) : _self(by), _canDestruct(true) {}

    /**
     * @brief use in a for_each
     */
    void		operator()(Entity *);

    /**
     * @return @a BombExplode::TryDestruct::_canDestruct
     * @brief return if the object can be destroy
     */
    bool		canDestruct() const {return _canDestruct;}
  };
  /**
   * @class Explosion
   * @brief make the explosion
   */
  class		Explosion
  {
    /**
     * @brief explosion range
     */
    unsigned int	_range;
    /**
     * @brief the bomb which's explode
     */
    Entity		*_owner;

    /**
     * @brief the bomb position
     */
    Position	const *_pos;

    /**
     * @brief the fire hotbox
     */
    Hitbox	const *_hitbox;
  private:
    /**
     * @brief the explosion area
     */
    bool	explodeArea(glm::vec3 const& pos, float dx, float dy);

    /**
     * @brief choose what texture do for fire
     */
    void	chooseTexture(float dx, float dy, std::string & textureFire);

    /**
     * @brief choose what texture do for end of fire
     */
    void	chooseEnd(float dx, float dy, std::string & textureFire);

    /**
     * @brief choose the side in @a BombExplode::Explosion::chooseEnd
     */
    const std::string chooseSide(float, const std::string, const std::string);
  public:
    /**
     * @brief a basic contructor
     */
    Explosion(unsigned int range, Position const *pos, Hitbox const *hit, Entity *owner);

    /**
     * @brief make the bomb explosion
     */
    void	explode();
  };
  /**
   * @brief make the bomb explosion
   */
  void		explode(glm::vec3 const& pos);
public:
  /**
   * @brief the basic contructor
   */
  BombExplode(unsigned int range) : _range(range) {}
  /**
   * @brief destroy the bomb
   */
  virtual void	destroy();
  /**
   * @brief the loaded contructor
   */
  BombExplode(std::istream & is) { is >> _range;}

  /**
   * @brief the basic destructor
   */
  virtual ~BombExplode() {}

  /**
   * @brief save the entity
   */
  virtual void	saveSelf(std::ostream&) const;

  /**
   * @return BombExplode::Explosion::_range
   * @brief return the range
   */
  unsigned int getRange() const {return _range;}
};

#endif /* !DESTRUCTION_HH_ */
