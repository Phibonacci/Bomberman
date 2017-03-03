#ifndef ISCENE_H_
# define ISCENE_H_

# include "IObject.hh"

/**
 * @brief the scene interface
 */
class	IScene : public IObject
{
public:
  /**
   * @param scr the screen
   * @brief sreen initialize function
   */
  virtual void	initScreen(Screen::AScreen &scr) = 0;
  /**
   * @brief the basic destructor
   */
  virtual ~IScene() {}
};

#endif /* !ISCENE_H_ */
