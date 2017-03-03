#ifndef CASE_HH_
# define CASE_HH_

/**
 **@class Case
 **@brief This class contains all the variables for the first run through the map, its creation and first algorithm
 */
class		Case
{
public:

  /**
  **@enum DirWall
  **@brief This enum allows the program to check each directions of a Case to see wether the walls are opened or note
  */
enum		DirWall
  {
    UP,
    RIGHT,
    DOWN,
    LEFT,
  };

enum		Verb
  {
    NO,
    YES,
  };

enum		Type
  {
    WALL = 0,
    BREAK,
    FREE,
    SPAWN,
  };

private:

  /**
   **@var Walls
   **@brief this is an array of bool, useful to know wich directions are available
   */
  bool		Walls[4];

  /**
   **@var x
   **@brief x coordonate of the Case
   */
  int		x;

  /**
   **@var y
   **@brief y coordonate of the Case
   */
  int		y;


  /**
   **@var beenVisited
   **@brief only to check if the case has already been visited
   */
  Verb		beenVisited;

  /**
   **@var isWhat
   **@brief only here to store what kind of case it is
   */
  Type		isWhat;

public:
  Case(const int &, const int &);
  ~Case();
  Case();
  Case		&operator=(const Case &);

  void		setX(const int &);
  void		setY(const int &);

  /**
   **@fn setWall
   **@brief most iportant function here, sets the wall to allow passage of the program during the algorithm
   */
  void		setWall(const DirWall &, const bool);
  void		setVisit(Verb);
  void		setType(Case::Type t);

  int		getY() const;
  int		getX() const;
  Verb		getVisited() const;
  Type		getType();
  void		getWall(bool *);
};

#endif
