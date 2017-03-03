#ifndef __DRAWMODEL_HH__
# define __DRAWMODEL_HH__

#include <Model.hh>
#include <glm/glm.hpp>

/**
 * @class DrawModel
 * @brief the model draw generator
 */
class DrawModel
{
  /**
   * @var _model
   * @brief the model to draw
   */
  gdl::Model	_model;

  /**
   * @var _ratio
   * @brief the ratio model size
   */
  glm::vec3	_ratio;

  /**
   * @var _mapModel
   * @brief the generated model map
   */
  static std::map<std::string, DrawModel*> _mapModel;

public:
  /**
   * @typedef DMptr
   * @brief the model function pointer
   */
  typedef void (DrawModel::*DMptr)();

  DrawModel();

  /**
   * @brief the desctructor
   */
  ~DrawModel();

  /**
   * @brief initialize the @a DrawModel
   */
  static void		initialize();

  /**
   * @param str the string choose what model to return
   * @return the model corresponding to the string @a str
   * @brief return a model correspoding to the string
   */
  static DrawModel*	getDrawModel(std::string const& str);

  /**
   * @return the model class
   * @brief return the model class
   */
  gdl::Model&		getModel();

  /**
   * @return the ratio class
   * @brief return the ratio class
   */
  glm::vec3&		getRatio();

  /**
   * @param str the string to chage
   * @brief charge a model with the string
   */
  void	charge(const std::string & str);

  /**
   * @brief apply the animation of the model
   */
  void	applyAnimation(const std::string &, const std::string &);
};

#endif // !__DRAWMODEL_HH__
