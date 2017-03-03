#ifndef ASUBSCREEN_H_
# define ASUBSCREEN_H_

# include <glm/glm.hpp>
# include <AShader.hh>
# include "ACamera.hh"

namespace Screen
{
  /**
   * @class ASubScreen
   * @brief allows manipulation of split screen
   */
  class ASubScreen
  {
    glm::vec2	_pos;
    glm::vec2	_size;
    ACamera	*_camera;
  public:
    ASubScreen(ACamera *camera);
    /**
     * @brief allows to know whether or not the object is in this screen
     */
    virtual bool	isInScreen(glm::vec3 const & pos3d, glm::vec3 const& size3d) const;
    /**
     * @brief applies the screen in use
     */
    void	apply(gdl::AShader &) const;

    /**
     ** Returns the position of the screen
     */
    glm::vec2	&getPos() {return _pos;}

    /**
     ** Returns the size of the screen
     */
    glm::vec2	&getSize() {return _size;}
    /**
     ** Returns the position of the screen
     */
    glm::vec2	const &getPos() const {return _pos;}
    /**
     ** Returns the size of the screen
     */
    glm::vec2	const &getSize() const {return _size;}

    /**
     ** Returns the center position of the screen
     */
    glm::vec2	getCenter() const;

    /**
     ** Returns the camera associated of the screen
     */
    ACamera	*getCamera() const {return _camera;}

    /**
     ** Returns the camera associated of the screen
     */
    ACamera	*&getCamera() {return _camera;}
    virtual ~ASubScreen();
  };
};

#endif /* !ASUBSCREEN_H_ */
