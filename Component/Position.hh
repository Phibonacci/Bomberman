/**
 * @file Position.hh
 */
#ifndef POSITION_HH_
# define POSITION_HH_

# include <glm/glm.hpp>
# include "AComponent.hh"
# include "Board.hh"

/**
 * @class Position
 * @brief Component that holds the position
 */
class	Position : public AComponent
{
protected:
  /**
   * @var _map
   * @brief map that the Component need to verify its collision
   */
  Board		*_map;
  /**
   * @var _position
   * @brief current position (x,y,z)
   */
  glm::vec3	_position;
public:
  /**
   * @fn getPos
   * @brief return the _position
   */
  glm::vec3 &		getPos() {return _position;}
  /**
   * @fn getPos
   * @brief return the _position
   */
  glm::vec3 const&	getPos() const {return _position;}
  /**
   * @fn getBoardIn
   * @brief return a pointer on the _map
   */
  Board *		getBoardIn() const {return _map;}
public:
  /**
   * @brief constructor
   */
  Position(Board *map) : _map(map), _position(0, 0, 0) {}
  /**
   * @brief constructor
   */
  Position(Board *map, glm::vec3 const &pos) : _map(map), _position(pos) {}
  /**
   * @brief constructor for the loadgame
   */
  Position(std::istream &);
  /**
   * @fn ~Position
   * @brief destructor
   */
  virtual ~Position() {}
  /**
   * @fn saveSelf
   * @brief save the bonus when the game is save
   */
  virtual void	saveSelf(std::ostream&) const;
};

#endif /* !POSITION_HH_ */
