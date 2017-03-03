#ifndef __EDITMAKE_HPP__
# define __EDITMAKE_HPP__

# include <Input.hh>
# include <Clock.hh>
# include "AComponent.hh"
# include "EntityFactory.hh"
# include "Info.hpp"
# include "MapEditor.hpp"

class Player;

/**
 * @brief the class for edit player
 */
class	EditMake : public AComponent
{
public:
  /**
   * @brief the entity type which's can be created
   */
  typedef enum	typeWall
    {
      WALL,
      INDE,
      MOVE,
      TELEPORT,
      DEL,
      PLAYER,
      AI,
      MAX
    }	TWall;

  /**
   * @brief method function pointer
   */
  typedef	Entity* (*fnct)(Board*, glm::vec3 const&, Info::Mod);

private:
  /**
   * @brief the map translator between the enum and a @a EditMake::fnct
   */
  static std::map<TWall, fnct>		_map;

  /**
   * @brief the actual entity which's choosen
   */
  int					_val;

public:

  /**
   * @brief the basic contructror
   */
  EditMake() {_val = 0;}
  /**
   * @return @a EditMake::_val
   * @return the value
   */
  int	&getVal();

  /**
   * @brief put a wall on the board
   */
  void	makeWall(Player *player, MapEditor&);

  /**
   * @brief clear the map
   */
  void	clearMap();

  /**
   * @brief save the component
   */
  virtual void	saveSelf(std::ostream&) const;

  /**
   * @brief the basic destructor
   */
  virtual ~EditMake() {}
};

/**
 * @brief component for the player who's edit the map
 */
class	EditMaker : public AUpdateComponent
{
private:

  /**
   * @brief the @a MapEditor
   */
  MapEditor&				_edit;

  /**
   * @brief the cooldown before put another block
   */
  float	_coolDown;
public:
  /**
   * @brief a basic contructor
   */
  EditMaker(MapEditor& edit) : _edit(edit), _coolDown(0) {}

  /**
   * @brief change the draw component to the edit player
   */
  void			changeDrawComponent(Player *& player, int val);

  /**
   * @brief save the component
   */
  virtual void	saveSelf(std::ostream&) const;

  /**
   * @brief check the input pressed by the user and make the job
   */
  virtual void		update(gdl::Clock const &clock, gdl::Input &input);

  /**
   * @brief a basic destructor
   */
  virtual ~EditMaker() {}
};


#endif // !__EDITMAKE_HPP__
