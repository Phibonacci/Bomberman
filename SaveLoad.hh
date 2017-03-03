#ifndef SAVELOAD_H_
# define SAVELOAD_H_

# include <glm/glm.hpp>
# include <iostream>
# include "AComponent.hh"
# include "Board.hh"
# include <string>
# include "GameParty.hh"

/**
 * @brief save and load a game
 */
class	SaveLoad
{
  /**
   * @brief the current save
   */
  static GameParty		*current_save;
private:
  /**
   * @brief load an entity
   */
  static void	loadEntity(std::istream &is);
public:
  /**
   * @brief the basic contructor
   */
  SaveLoad(GameParty *);
  /**
   * @brief the basic destructor
   */
  ~SaveLoad();
  /**
   * @brief save a vec3
   */
  static void	saveVec3(std::ostream &os, glm::vec3 const&);
  /**
   * @brief load a vec3
   */
  static void	loadVec3(std::istream &os, glm::vec3 &);
  /**
   * @return @a SaveLoad::current_save
   * @brief return the current save
   */
  static GameParty	const *getCurrent();

  /**
   * @brief load a game
   */
  void	loadBoard(Board *&, std::ifstream &is);

  /**
   * @param file the filename to save
   * @brief save the game
   */
  void	saveParty(std::string const& file);

  /**
   * @brief save the game with default filename
   */
  void	saveParty();
  /**
   * @brief open the file for @a SaveLoad::loadBoard
   */
  void	loadParty(std::string const& file);
};

#endif /* !SAVELOAD_H_ */
