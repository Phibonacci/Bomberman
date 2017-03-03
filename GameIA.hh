#ifndef GAMEIA_H_
# define GAMEIA_H_

# include "Thread.hh"
# include "Board.hh"

# include "Entity.hpp"
# include <vector>
# include <Input.hh>

/**
 ** @brief Namespace for Controller
 */
namespace Controller {
  class AI;
}

class GameParty;

/**
 * @brief give information about player to ais
 */
class PlayerInfo
{
private:
  /**
   * @brief ai controller
   */
  Controller::AI *_AI;

  /**
   * @brief the player
   */
  Player const * _player;

  /**
   * @brief the player position
   */
  glm::vec2 _position;

public:
  /**
   * @param AI the @a Controller::AI
   * @param player the @a Player
   * @brief basic contructor
   */
  PlayerInfo(Controller::AI * AI, Player const *player);

  /**
   * @brief the basic destructor
   */
  ~PlayerInfo();

public:
  /**
   * @return @a PlayerInfo::_position
   * @brief return the player position
   */
  glm::vec2 const & getPosition() const;

  /**
   * @brief set @a PlayerInfo::_AI
   */
  void		setIA(Controller::AI *);

  /**
   * @brief update @a PlayerInfo::_AI
   */
  bool		updateIA();

  /**
   * @brief update @a PlayerInfo::_position
   */
  bool		positionUpdate();
};

/**
 * @brief give map information to ais
 */
class MapInfo : public std::vector< std::vector <int> >
{
public:
  /**
   * @brief the basic contructor
   */
  MapInfo(int, int);

  /**
   * @brief the basic destructor
   */
  ~MapInfo();
public:
  /**
   * @param coord the entity position
   * @brief return the entity to this position
   */
  int		getPosition(glm::vec3 const & coord) const;

  /**
   * @return the map width
   * @brief return the map width
   */
  size_t	getWidth() const;

  /**
   * @return the map height
   * @brief return the map height
   */
  size_t	getHeight() const;

};

/**
 * @brief ai manager
 */
class GameIA : public CThread::IThreadObj
{
public:

  /**
   * @brief enum for entity map translation
   */
  enum item {
    NONE	= 0b00000001,
    SBLOCK	= 0b00000010,
    DBLOCK	= 0b00000100,
    BONUS	= 0b00001000,
    PLAYER	= 0b00010000,
    DANGER	= 0b00100000,
    FIRE	= 0b01000000,
    BOMB	= 0b10000000
  };

private:
  /**
   * @brief update ais
   */
  class CheckMover
  {
  public:
    /**
     * @brief the basic contructor
     */
    CheckMover();
    /**
     * @brief update ais and check if ais are alive
     */
    void	operator()(PlayerInfo *);

    /**
     * @brief return GameIA::CheckMover::_alive
     */
    int		getAlive() const {return _alive;}
  private:

    /**
     * @brief how many ai is alive
     */
    int		_alive;
  };
public:
  /**
   * @brief how many ai is alive
   */
  int		_alive;
  /**
   * @param owner the @a GameParty
   * @brief basic contructor
   */
  GameIA(GameParty *owner);

  /**
   * @brief the basic destructor
   */
  virtual ~GameIA();

  /**
   * @brief call @a refresh and update ais with a for_each calling GameIA::CheckMover
   */
  virtual void	execute();

  /**
   * @brief add a new ai
   */
  Controller::AI	*addNewIA(Player const * pl);

  /**
   * @brief stop @a GameIA::execute
   */
  void			stop();
private:
  /**
   * @brief copy constructor
   */
  GameIA(const GameIA &);

  /**
   * @brief = operator for GameIA
   */
  GameIA &operator=(const GameIA &);
private:
  /**
   * @brief add something to the map
   */
  void			addToMap(int, glm::vec3 const&);

  /**
   * @brief get case information
   */
  int			getCase(glm::vec3 const&);

  /**
   * @brief refresh @a MapInfo
   */
  void			refreshMap(Board *);

  /**
   * @brief refesh all
   */
  void			refresh();

  /**
   * @brief add a zone where where could be are fire
   */
  void			addBombZone(size_t width, size_t height);

  /**
   * @brief put a bomb on @a MapInfo
   */
  void			putBomb(Entity const *, glm::vec3 const& coord);

  /**
   * @brief put fire on @a MapInfo
   */
  void			putFire(Entity const *, glm::vec3 const& coord);

  /**
   * @brief put a bonus on @a MapInfo
   */
  void			putBonus(Entity const *, glm::vec3 const& coord);

  /**
   * @brief put a block on @a MapInfo
   */
  void			putBlock(Entity const *, glm::vec3 const& coord);
  void			putPlayer(Entity const *, glm::vec3 const& coord);
  void			selectParts(Board *board);
  void			refreshParts(Board *board);
  void			clearZone(glm::vec3 const & coord);

private:
  /**
   * @brief the @a GameParty
   */
  GameParty		*_party;
private:
  /**
   * @brief the @a GamePlayer::_players
   */
  std::vector< PlayerInfo * > _players;

  /**
   * @brief the @a MapInfo
   */
  MapInfo		_map;

private:
  /**
   * @brief if true stop exectute else false
   */
  bool			_needStop;

private:
  /**
   * @brief bomb zone to draw on _map
   */
  class BombZone {
  public:
    /**
     * @brief the bomb position
     */
    glm::vec3 const	_position;

    /**
     * @brief the bomb range
     */
    size_t		_range;

    /**
     * @return @a GameAI::BombZone::_position
     * @brief return the bomb position
     */
    glm::vec3 const &	getPosition() const;

    /**
     * @return @a GameAI::BombZone::_range
     * @brief return the bomb range
     */
    size_t		getRange() const;

    /**
     * @brief a basic contructor
     */
    BombZone(glm::vec3 const & position, int range);

    /**
     * @brief a basic destructor
     */
    ~BombZone();
  };
  /**
   * @brief contrain all the GameIA::BombZone
   */
  std::stack<BombZone *> _bombstack;
  std::list<Part *>	_parts;
  std::vector< std::string > _files;

protected:

};

#endif /* !GAMEIA_H_ */
