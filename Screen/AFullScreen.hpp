#ifndef __AFULLSCREEN_HPP__
# define __AFULLSCREEN_HPP__

# include "ASubScreen.hh"

namespace Screen
{
  /**
   * @class AFullScreen
   * @brief A specialized subscreen that covers full screen
   */
  class AFullScreen : public ASubScreen
  {
  public:
    AFullScreen(ACamera *camera)
    : ASubScreen(camera)
    {}
    virtual bool	isInScreen(glm::vec3 const &, glm::vec3 const&) const
    {
      return (true);
    }
    virtual ~AFullScreen() {}
  };

};
#endif // !__AFULLSCREEN_HPP__
