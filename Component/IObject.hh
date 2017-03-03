/**
 * @file IObject.hh
 */
#ifndef IOBJECT_H_
# define IOBJECT_H_

# include <SdlContext.hh>
# include <BasicShader.hh>
# include "AScreen.hh"

/**
 * @class IObject
 * @brief Interface who update and draw on the screen
 */
class	IObject
{
public:
  /**
   * @fn update
   * @brief update the object
   */
  virtual int update(gdl::Clock const &clock, gdl::Input &input) = 0;
  /**
   * @fn draw
   * @brief draw on the screen the object
   */
  virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock) = 0;
  /**
   * @fn ~IObject
   * @brief destructor
   */
  virtual ~IObject() {}
};

#endif /* !IOBJECT_H_ */
