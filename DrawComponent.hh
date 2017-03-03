#ifndef __GENDRAWCOMPONENT_HH__
# define __GENDRAWCOMPONENT_HH__

# include <Texture.hh>
# include <Geometry.hh>
# include <map>
# include "ConfigLoader.hpp"
# include "AScreen.hh"

# define UNDESTRUCTIBLE_WALL_TEXTURE	("assets/image/wall/unwall.tga")
# define DESTRUCTIBLE_WALL_TEXTURE	("assets/image/wall/wall.tga")
# define FIRE_TEXTURE			"assets/image/explosion/fire[explosion].tga"
# define FIRE_TURN_TEXTURE		"assets/image/explosion/fire[turn].tga"
# define FIRE_CROSS_TEXTURE		"assets/image/explosion/fire[cross2].tga"
# define FIRE_END_UP_TEXTURE		"assets/image/explosion/fire[end_up].tga"
# define FIRE_END_RIGHT_TEXTURE		"assets/image/explosion/fire[end_right].tga"
# define FIRE_END_LEFT_TEXTURE		"assets/image/explosion/fire[end_left].tga"
# define FIRE_END_DOWN_TEXTURE		"assets/image/explosion/fire[end_down].tga"

# define	BONUS_RANGE		"assets/image/bonus/bonusRange.tga"
# define	MALUS_RANGE		"assets/image/bonus/MalusRange.tga"
# define	BONUS_SPEED		"assets/image/bonus/bonusSpeed.tga"
# define	MALUS_SPEED		"assets/image/bonus/MalusSpeed.tga"
# define	BONUS_STOCK		"assets/image/bonus/bonusStock.tga"
# define	MALUS_STOCK		"assets/image/bonus/MalusStock.tga"
# define	SKULL			"assets/image/bonus/Skull.tga"
# define	PIERCE_BOMB		"assets/image/bonus/BombPierce.tga"
# define	KICK_BOMB		"assets/image/bonus/BombKick.tga"
# define	TELEPORT_BONUS		"assets/fbx/teleport.fbm/teleport.tga"

# define	GENMENUCREDITS "assets/image/menu/credits_menu.tga"
# define	GENMENUVIRGIN "assets/image/menu/virgin_menu.tga"
# define	GRASS_TEXTURE "assets/image/ground/grass.tga"
# define	GENMENUSTART1 "./assets/image/menu/background.tga"
# define	GENMENUSTART2 "./assets/image/menu/background2.tga"
# define	GENMENUMAIN "./assets/image/menu/bombermanMenu.tga"
# define	GENMENUPLAY "./assets/image/menu/MenuPlay.tga"
# define	GENMENUBOMB "./assets/image/menu/Bomb.tga"

/**
 * @class DrawComponent
 * @brief generate component to draw
 */
class	DrawComponent
{

  /**
   * @var _texture
   * @brief the texture to draw
   */
  gdl::Texture	_texture;

  /**
   * @var _geometry
   * @brief the component geometry
   */
  gdl::Geometry	*_geometry;

  /**
   * @var _mapComponent
   * @brief the created components map
   */
  static std::map<std::string, DrawComponent*> _mapComponent;

  /**
   * @var _mapLetters
   * @brief the created letters map
   */
  static std::map<char, DrawComponent*> _mapLetters;

  /**
   * @var size_text
   * @brief the text size
   */
  static float const			size_text;
public:

  /**
   * @typedef DCptr
   * @brief the method function pointer type
   */
  typedef void (DrawComponent::*DCptr)(std::string const&, int const, int const);

  /**
   * @param ptr the function pointer called in the function
   * @param str the string in parameter in @a ptr
   * @param x the int parameter in @a ptr
   * @param y the int parameter in @a ptr
   * @brief the contructor
   */
  DrawComponent(DCptr ptr, std::string const& str, int const x, int const y);

  /**
   * @param x the up left corner of the cut picture
   * @param y the down left corner of the cut picture
   * @param xx the up right corner of the cut picture
   * @param yy the down right corner of the cut picture
   * @brief the contructor
   */
  DrawComponent(float x, float y, float xx, float yy);

  /**
   * @brief the destructor
   */
  ~DrawComponent();

  /**
   * @brief initialize variables in the class
   */
  static void		initialize();

  /**
   * @brief return the texture
   */
  gdl::Texture const&	getTexture() const;

  /**
   * @brief return the gemometry
   */
  gdl::Geometry		*getGeometry() const;

  /**
   * @param str picture's path
   * @param x size
   * @param y size
   * @brief generate wall draw component
   */
  void			genBonus(std::string const& str = "", int const x = 0, int const y = 0);

  /**
   * @param str picture's path
   * @param x size
   * @param y size
   * @brief generate wall draw component
   */
  void			genWall(std::string const& str = UNDESTRUCTIBLE_WALL_TEXTURE,
				int const x = 0,
				int const y = 0);
  /**
   * @param str picture's path
   * @param x size
   * @param y size
   * @brief generate wall undestructible draw component
   */
  void			genUnWall(std::string const& str = UNDESTRUCTIBLE_WALL_TEXTURE,
				  int const x = 0,
				  int const y = 0);
  /**
   * @param str picture's path
   * @param x size
   * @param y size
   * @brief generate fire draw component
   */
  void			genFire(std::string const& str = FIRE_TEXTURE,
				int const x = 0,
				int const y = 0);

  /**
   * @param str picture's path
   * @param x size
   * @param y size
   * @brief generate ground draw component
   */
  void			genGround(std::string const& str = GRASS_TEXTURE, int const x = 0, int const y = 0);

  /**
   * @param str picture's path
   * @brief generate ground draw component
   */
  static DrawComponent const* getComponent(std::string const& str);

  /**
   * @param x the up left corner of the cut picture
   * @param y the down left corner of the cut picture
   * @param xx the up right corner of the cut picture
   * @param yy the down right corner of the cut picture
   * @brief generate letters
   */
  void	genLetters(float x, float y, float xx, float yy);

  /**
   * @param str the str to write
   * @param vec where to write the string
   * @param screen the screen
   * @param clock the clock
   * @brief write the string @a str in the screen @a screen
   */
  static void   putstring(const std::string &str, glm::vec3 vec, Screen::AScreen &screen, const gdl::Clock &clock);

  /**
   * @param str the str to write
   * @param pos where to write the string
   * @param scr the screen
   * @param subscr the subscreen
   * @param scalevec the vector to scale
   * @brief write the string @a str in the screen @a screen
   */
  static void	putsSubScreen(std::string const& str, glm::vec2 const& pos,
			      Screen::AScreen &scr,
			      Screen::ASubScreen const& subscr,
			      glm::vec3 const& scalevec);
  static void	putsSubScreen(std::string const& str, glm::vec3 const& pos,
			      Screen::AScreen &scr,
			      Screen::ASubScreen const& subscr,
			      glm::vec3 const& scalevec);

  /**
   * @param c the letter to return
   * @return the picture corresponding to the letter @a c
   * @brief return the picture corresponding to @a c
   */
  static DrawComponent const *getLetter(char c);
};

#endif // !__GENDRAWCOMPONENT_HH__
