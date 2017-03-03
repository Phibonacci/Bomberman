#ifndef ACAMERA_H_
# define ACAMERA_H_

#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <AShader.hh>

class	Player;

namespace Screen
{
  /**
   * @class ACamera
   * @brief A basic camera
   */
  class ACamera
  {
  private:
    /**
     * @brief the projection used for all cameras
     */
    static glm::mat4 const	projection;
  protected:
    /**
     * @var _lookAt
     * @brief the position that the camera is aiming
     */
    glm::vec3		_lookAt;
    /**
     * @var _cameraDiff
     * @brief the difference between position aimed and position of the camera
     */
    glm::vec3		_cameraDiff;
  private:
    glm::mat4		getTransformation() const;
  public:
    ACamera();
    glm::vec3		&getLookAt();
    glm::vec3		&getCameraDiff();
    /**
     * @fn apply
     * @brief applies the camera on the given shader
     */
    void		apply(gdl::AShader &);
    /**
     * @fn range
     * @brief gives the approximate range that the camera covers
     */
    glm::vec2		range(glm::vec2 const & screensize) const;
    virtual void	update() {}
    virtual ~ACamera() {}
  };

  /**
   * @class AutoCamera
   * @brief A camera that traces the player on update
   */
  class AutoCamera : public ACamera
  {
  private:
    Player	*_tofollow;
  public:
    AutoCamera(Player *);
    virtual void	update();
    virtual ~AutoCamera() {}
  };
};

#endif /* !ACAMERA_H_ */
