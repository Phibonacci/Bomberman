#ifndef CONTENT_HH_
# define CONTENT_HH_

# include <vector>
# include <stack>

# include "Case.hh"
# include "maRand.hh"

/**
 **@brief This is an enum for cases in Map generation table
 */
enum		Types
  {
    FREE,
    WALL = 1,
    BREAK = 2,
    SPAWN = 3,
    TP = 7,
    INDE = 8,
    RESERVED = 9,
  };

/**
 **@class Content
 **@brief Class for all map generation
 */
class						Content
{
 public:
  Content(int x, int y);
  ~Content();
  Content();
  Content		&operator=(const Content &);
  Content(const Content &);

 private:
  /**
   **@var x
   **@brief Size from up to bottom
   */
  int						x;

  /**
   **@var y
   **@brief Size from left to write
   */
  int						y;

  /**
   **@var rand
   **@brief is a variable used to get random numbers
   */
  maRand					rand;

  /**
   **@brief Stack needed for recursive backtracking
   */
  std::stack<int*>				mastack;

  /**
   **@brief First map, made of Case
   */
  std::vector<std::vector<Case> >		all;

  /**
   **@brief Function pointers to factorize
   */
  void (Content::*ptr[4])(int &, int &);

  /**
   **@brief Function pointers to factorize
   */
  void (Content::*removePtr[4])(std::vector<std::vector<Types> > &, int , int );

  /**
   **@brief Funtion pointers to factorize
   */
  int (Content::*checkPtr[4])(std::vector<std::vector<Types> > &, int , int );

  /**
   **@brief Function pointer to factorise
   **@param x and @param y currently being checked
   **@param placed variable, counting the number of players placed and count, counting the number of blocks checked
   **@brief max @param x and max @param y
   **@brief the current @param map
   **@brief where the check @param started
   */
  int (Content::*playerptr[4])(int &, int &, int &, int &, int &, int &, std::vector<std::vector<Types> > &, int &, int &);

  /**
  **@brief Needed to check available directions
  */
  std::vector<Case::DirWall>			dto;

public:

  int						getX() const;
  int						getY() const;

  /**
   **@fn core
   **@brief This function will make the first run through the map
   **@param x and @param y to start and continue, these are random
   */
  int						core(int &x, int &y);

  /**
   **@fn getDir
   **@brief This function gets the directions where the program can go throught the first run
   **@param x current x
   **@param y current y
   **@param temp the map
   **@param T to check or not
   */
  void						getDir(int x, int y, std::vector<Case::DirWall> &temp, Case::Verb T) const;

  /**
   **@fn goUp
   **@fn goRight
   **@fn goDown
   **@fn goLeft
   **@brief These are factorised functions to produce a generic code
   **@param x and @param y to check around the case
   */
  void						goUp(int &, int &);
  void						goLeft(int &, int &);
  void						goDown(int &, int &);
  void						goRight(int &, int &);

  /**
   **@fn Convert
   **@brief This functions converts the case map into Types enums, to manipulate it better. This is the second run through the map
   **@brief the double @a vector in which the new map is created
   **@brief an @a int to choose between a perfect maze, and a not-so-perfect maze
   */
  void						Convert(std::vector<std::vector<Types> > &, int);

  /**
   **@fn endConvert
   **@brief This functions freeqs space in converts and terminates the conversion
   **@brief the @a map almost finished, a double vector of Types
   */
  void						endConvert(std::vector<std::vector<Types> > &);

  /**
   **@fn checkUp
   **@fn checkRight
   **@fn checkDown
   **@fn checkLeft
   **@brief These are factorised functions to produce a generic code
   */
  int						checkUp(std::vector<std::vector<Types> > &temp, int i, int j);
  int						checkRight(std::vector<std::vector<Types> > &temp, int i, int j);
  int						checkDown(std::vector<std::vector<Types> > &temp, int i, int j);
  int						checkLeft(std::vector<std::vector<Types> > &temp, int i, int j);

  /**
  **@fn isFreeAround
  **@brief This function calls the checks, to verify if blocks around are free
  **@brief the @a temp and the position in @a i an @a j of the case being checked
  */
  bool						isFreeAround(std::vector<std::vector<Types> > &temp, int i, int j);

  /**
   **@fn removeUp
   **@fn removeRight
   **@fn removeDown
   **@fn removeLeft
   **@brief These are factorised functions to produce a generic code
   */
  void						removeUp(std::vector<std::vector<Types> > &temp, int i, int j);
  void						removeRight(std::vector<std::vector<Types> > &temp, int i, int j);
  void						removeDown(std::vector<std::vector<Types> > &temp, int i, int j);
  void						removeLeft(std::vector<std::vector<Types> > &temp, int i, int j);

  /**
   **@fn Finalyze
   **@brief This function finishes the map generation, without the players for the moment. This is the third run through.
   **@brief the map again
   **@param temp the map
   **@param ratioFree is the ration of free blocks (removing destructible blocks)
   **@param ratioUnbreak is the ratio of undestructible blocks left. A 100% will not remove any blocks.
   */
  void						Finalyze(std::vector<std::vector<Types> > &temp, int ratioFree, int ratioUnbreak);

  /**
   **@fn putPlayer
   **@brief This function puts the players into the map, this is the fourth run through the map
   **the @param nb number of players to put
   **the @param temp the map
   */
  void						putPlayer(int, std::vector<std::vector<Types> > &temp, int nb);

  /**
   **@fn dirPlayerUp
   **@fn dirPlayerRight
   **@fn dirPlayerDown
   **@fn dirPlayerLeft
   **@brief These are factorised functions to produce a generic code
   */
  int						dirPlayerUp(int &, int &, int &, int &, int &, int &, std::vector<std::vector<Types> > &, int &, int &);
  int						dirPlayerRight(int &, int &, int &, int &, int &, int &, std::vector<std::vector<Types> > &, int &, int &);
  int						dirPlayerDown(int &, int &, int &, int &, int &, int &, std::vector<std::vector<Types> > &, int &, int &);
  int						dirPlayerLeft(int &, int &, int &, int &, int &, int &, std::vector<std::vector<Types> > &, int &, int &);

  /**
   **@fn getDirSpawn
   **@brief This function gets the directions where the program can go to put a player
   **@brief the @a maximum of @a x and @a y
   **@brief a @a vector to store the possible directions
   **@brief the @a map of course
   **@brief the current @a x and @a y
   */
  void						getDirSpawn(int, int, std::vector<Case::DirWall> &, std::vector<std::vector<Types> > &, int, int) const;

  /**
   **@fn getSpawn
   **@brief This function gets a spawn place for a player
   **@brief the @a map
   **@brief the size of the @a map, in @a x and @a y
   **@brief a place to put a spawn, in @a i an @a j
   **@brief the number of players @a placed
   */
  int						getSpawn(std::vector<std::vector<Types> > &, int, int, int, int, int &);

  /**
   **@fn isOk
   **@brief checks if its ok, duh
   */
  bool						isOk(int x, int y) const;

  /**
  **@fn ifPlace
  **@brief checks if its placed...
  */
  void						ifPlace(bool dto[4], std::vector<std::vector<Types> > &, int , int);
};

#endif
