#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include <list>

class Teleport;

/**
 ** This class is used to create and activate teleporters
 ** @brief Generates the teleporters travels
 */
class	TeleportCenter
{
  /**
   * @brief teleporter list
   */
  static std::list<Teleport *>	_teleports;
public:
  /**
   * @brief add a teleport to the list @a _teleports
   */
  static void	addTeleport(Teleport *);

  /**
   ** @brief This function Removes a teleporter from the list
   ** @param t
   */
  static void	removeTeleport(Teleport *);

  /**
   ** @brief This function returns the teleporter next to the parameter
   ** @param t
   ** @return the next teleporter
   */
  static Teleport *getNextTeleport(Teleport *);
};

#endif /* !COMPONENTFACTORY_H_ */
