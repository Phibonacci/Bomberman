/**
 * @file Hitbox.hh
 */
#ifndef HITBOX_H_
# define HITBOX_H_

# include <glm/glm.hpp>
# include "AComponent.hh"

/**
 * @class Hitbox
 * @brief Component that holds the Hitbox
 */
class	Hitbox : public AComponent
{
protected:
  /**
   * @var _size
   * @brief the size of the hitbox in (x, y, z)
   */
  glm::vec3	_size;
public:
  /**
   * @brief return the size
   */
  glm::vec3 &		getSize() {return _size;}
  /**
   * @brief return the size
   */
  glm::vec3 const&	getSize() const {return _size;}
public:
  /**
   * @brief just a basic constructor with no parameter
   */
  Hitbox() : _size(1, 1, 1) {}

  /**
   * @brief just a basic constructor with size in parameter
   */
  Hitbox(glm::vec3 const &size) : _size(size) {}

  /**
   * @brief constructor for load the data {loadgame}
   */
  Hitbox(std::istream &);

  /**
   * @fn ~Hitbox
   * @brief a basic destructor
   */
  virtual ~Hitbox() {}

  /**
   * @fn saveSelf
   * @brief this function save the data {savegame}
   */
  virtual void	saveSelf(std::ostream &os) const;
private:
  /**
   * @fn isInRange
   * @brief check if the hitbox is damaged
   */
  bool	isInRange(glm::vec3 const&) const;
public:
  /**
   * @fn isInTouch
   * @brief check if the hitbox damaged the target
   */
  bool	isInTouch(Hitbox const&) const;
};

#endif /* !HITBOX_H_ */
