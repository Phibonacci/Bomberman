#ifndef GAMEINTRO_H_
# define GAMEINTRO_H_

# include "IScene.hh"
# include "AScreen.hh"

class Entity;

/**
 ** @namespace Intro
 ** @brief Namespace for the Introduction
 */
namespace Intro
{
  /**
   ** @class GameInfo
   ** @brief Class for generating the game intro
   */
  class GameIntro : public IScene
  {
  public:
    GameIntro();
    virtual ~GameIntro();
    /**
     * @fn update
     * @brief update the object
     */
    virtual int update(gdl::Clock const &clock, gdl::Input &input);
    /**
     * @fn draw
     * @brief draw on the screen the object
     */
    virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock);
    virtual void initScreen(Screen::AScreen &scr);
  private:
    GameIntro(const GameIntro &);
    GameIntro &operator=(const GameIntro &);
  private:
    float		_introtime;
    Screen::ACamera *	_cam;
    Entity *		_person;
  };
}
#endif /* !GAMEINTRO_H_ */
