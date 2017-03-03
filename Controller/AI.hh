#ifndef AI_HH_
# define AI_HH_

# include <iostream>
# include <Input.hh>
# include "IControl.hh"
# include "Position.hh"
# include "lua5.2/lua.hpp"

class PlayerInfo;
class MapInfo;
class Player;

namespace	Controller {
  /**
   * @brief ai controller
   */
  class		AI : public IControl
  {
  public:
    /**
     * @brief the APIFunctions
     */
    class	APIFunctions
    {
    public:
      /**
       * @brief lua function pointer
       */
      int (*cfunction)(lua_State *);
      /**
       * @brief the lua name
       */
      std::string	lua_name;
    };


  private:
    /**
     * @brief enum for AIs moves
     */
    enum		move {
      UP = 0,
      DOWN,
      LEFT,
      RIGHT
    };

  private:
    /**
     * @brief a lua variable
     */
    lua_State*		_lua_state;

    /**
     * @brief a @a PlayerDir for ais move
     */
    PlayerDir		_dir;

    /**
     * @brief a @a Button for ais actions
     */
    Button		_button;

    /**
     * @brief a @a MapInfo for map information
     */
    MapInfo const *	_map;

    /**
     * @brief a @a PlayerInfo for player infomation
     */
    PlayerInfo const *	_player;

    /**
     * @brief a filename
     */
    std::string const	_file_name;

  private:
    int			_id;

    /**
     * @brief Boolean for dijktra algorithm
     */
    bool		_blocked;

    /**
     * @brief MapInfo for dijktra algorithm
     */
    MapInfo		 _dmap;

    /**
     * @brief where to go in x
     */
    float		_path_x;

    /**
     * @brief bitmask of cases to look for
     */
    int			_mask;

    /**
     * @brief boolean, specify to use a safe way
     */
    bool		_safe;

    /**
     * @brief where to go in y
     */
    float		_path_y;

    /**
     * @brief the current x
     */
    size_t		_x;

    /**
     * @brief the current y
     */
    size_t		_y;

    /**
     * @brief the value to check
     */
    int			_check_value;

  private:
    void		loadLibrarys();
    void		loadFile(std::string const & file_name);
    void		pushFunction(int (*func)(lua_State *),
				     std::string const & text);
    void		loadAPI(void);


  private:

    /**
     * @brief refresh the map
     */
    static void		refreshMap(AI *self);

    static bool		isExposedAux(AI *self, size_t x, size_t y);
    static bool		matchMask(int mask, int mask_in, int mask_out);
    static bool		pathFindingAux(AI *self, size_t from_x, size_t from_y,
				       size_t to_x, size_t to_y);
    static bool		pathToMask(AI *self);
    /**
     * @brief remove an invalid move
     */
    static void		removeInvalidMove(AI *self, size_t x, size_t y,
					  std::list<enum move> & lmove);

    /**
     * @brief fill around the ai
     */
    static bool		fillAround(AI *self, size_t x, size_t y,
				   bool & blocked);

    static bool		pathFirstStep(AI *self);
    static void		getFirstStep(AI *self);
    static bool		dijkstraFill(AI *self,
				     std::stack< glm::vec2 > * new_stack,
				     size_t x, size_t y);

    /**
     * @brief the dijkstra algorithm for ai path
     */
    static bool		dijkstra(AI *self, int mask, bool safe);
    static bool		amExposedAux(AI *self, size_t x, size_t y);

    /**
     * API functions
     */
  private:

    /**
     * @brief get the current position
     */
    static int		getPosition(lua_State *l);

    /**
     * @brief push map size for ai
     */
    static int		getMapSize(lua_State *l);

    /**
     * @brief it seem to be to test connection between c++ code and the lua
     */
    static int		exampleAPIFunction(lua_State *l);

    /**
     * @brief set @a Controller::AI::_dir
     */
    static int		setDirection(lua_State *l);

    /**
     * @brief put a bomb on the board
     */
    static int		putBomb(lua_State *l);

    /**
     * @brief get the angle to the lua
     */
    static int		getAngle(lua_State *l);

    /**
     * @brief check if ai is exposed
     */
    static int		isExposed(lua_State *l);

    /**
     * @brief try to find a safe position
     */
    static int		amExposed(lua_State *l);

    /**
     * @brief look for a way to a safe position
     * @return 2 int to lua, x and y of the closest case of the path
     */
    static int		safePosition(lua_State *l);


    /**
     * @brief check if destructible blocks are around (4 directions)
     * @return 1 int to lua for true and false
     */
    static int		brickAround(lua_State *l);

    /**
     * @brief look for a way to a destructible block
     * @return 2 int, x and y of the closest case of the path
     */
    static int		toBrick(lua_State *l);

    /**
     * @brief look for a safe way to a destructible block
     * @return 2 int, x and y of the closest case of the path
     */
    static int		toBrickSafe(lua_State *l);

    /**
     * @brief look for a way to a bonus
     * @return 2 int, x and y of the closest case of the path
     */
    static int		toBonus(lua_State *l);

    /**
     * @brief look for a safe way to a bonus
     * @return 2 int, x and y of the closest case of the path
     */
    static int		toBonusSafe(lua_State *l);

    /**
     * @brief move to a position
     */
    static int		simpleMoveTo(lua_State *l);

    /**
     * @brief returns true in case of danger at 1 case perimeter
     */
    static int		dangerAround(lua_State *l);

    /**
     * @brief disable any button (like putbomb)
     */
    static int		noButton(lua_State *l);

  public:
    /**
     * @brief a basic contructor
     */
    AI(std::string const & file_name,
       MapInfo const * map,
       PlayerInfo const *player);
    /**
     * @brief a basic destructor
     */
    ~AI();

  public:
    /**
     * @fn checkMove
     * @brief check and return player's move
     * @return players array move
     */
    virtual void	checkMove(gdl::Input& input);

    /**
     * @fn getDir
     * @brief Return @a _dir value
     * @return A @a _dir copy value
     */
    virtual PlayerDir const& getDir() const;
    /**
     * @fn getBut
     * @brief Return @a _but value
     * @return A @a _but copy value
     */
    virtual Button	getBut();

    /**
     * @brief run ais
     */
    void		run();
  };
};
#endif // !AI_HH_
