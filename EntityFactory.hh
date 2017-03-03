/**
 * @file EntityFactory.hh
 */
#ifndef __ENTITYFACTORY_HH__
# define __ENTITYFACTORY_HH__

# include "Board.hh"
# include "HasPlayer.hh"
# include "Info.hpp"
# include <glm/glm.hpp>

class Entity;

/**
 * @class EntityFactory
 * @brief the entity factory
 */
class EntityFactory
{
public:
  /**
   * @fn NewBlock
   * @brief create a block entity. This block can be destroy
   */
  static Entity* NewBlock(Board *board, glm::vec3 const &vec, Info::Mod = Info::NONE);
  /**
   * @fn NewUndestructibleBlock
   * @brief create a block entity. This block can't be destroy
   */
  static Entity* NewUndestructibleBlock(Board *board, glm::vec3 const &vec,
					Info::Mod = Info::NONE);
  /**
   * @fn NewTeleportBlock
   * @brief create a bonus block : teleport
   */
  static Entity* NewTeleportBlock(Board *board, glm::vec3 const& vec, Info::Mod mod);
  /**
   * @fn NewBeforeTpBlock
   * @brief create a bonus block : teleport hide in destructible block
   */
  static Entity* NewBeforeTpBlock();
  static Entity* DeleteBlock(Board *board, glm::vec3 const& vec, Info::Mod = Info::NONE);

  /**
   * @fn NewPlayer
   * @brief create a player with the model
   */
  static Entity* NewPlayer(Board *board, glm::vec3 const & vec, Player* player, Info::Mod = Info::NONE);

  /**
   * @fn NewBomb
   * @brief create a bomb with the model
   */
  static Entity* NewBomb(Board *board, glm::vec3 const & vec, Player* player);

  /**
   * @fn PierceBomb
   * @brief create a special bomb
   */
  static Entity* PierceBomb(Board *board, glm::vec3 const & vec, Player* player);
  /**
   * @fn NewFire
   * @brief create deflagration of the bomb
   */
  static Entity* NewFire(Board *board, glm::vec3 const & vec, glm::vec3 const & hitbox);
  /**
   * @fn selectBonus
   * @brief choose if the bonus is inside the block
   */
  static const std::string selectBonus(Entity * bonus, int i);
  /**
   * @fn NewEditPlayer
   * @brief create the player in the map editor
   */
  static Entity* NewEditPlayer(Board *board, glm::vec3 const& vec, Player* player);

private:
  /**
   * @brief choose if the bonus inside the block is a positive or negative bonus
   */
  template<class T>
  static const std::string	selectBonusOrMalus(Entity * bonus, int var, int rate, const std::string strBonus, const std::string strMalus);
  /**
   * @fn isASpecialBonus
   * @brief choose if the bonus inside the block is a special bonus
   */
  static int	isASpecialBonus(Entity *bonus, int var);
};

#endif // !__ENTITYFACTORY_HH__
