#ifndef MODELDRAW_H_
# define MODELDRAW_H_

# include <string>
# include <Model.hh>
# include <Texture.hh>
# include <Geometry.hh>
# include "AComponent.hh"
# include "DrawComponent.hh"
# include "DrawModel.hh"
# include "AScreen.hh"

/**
 * @brief the model draw class
 */
class ModelDraw : public ADrawComponent
{
protected:
  /**
   * @brief the model name
   */
  std::string		_name;

  /**
   * @brief the current amination
   */
  std::string		_currentAnime;

  /**
   * @brief the @a DrawModel contain the model
   */
  DrawModel*		_drawmodel;

  /**
   * @brief the shader
   */
  gdl::BasicShader	_shader;

public:
  /**
   * @param str the model name
   * @brief the contructor
   */
  ModelDraw(std::string const& str);

  /**
   * @param is buffer that contain variables in load
   * @brief load contructor
   */
  ModelDraw(std::istream & is);

  /**
   * @param anime the anim use to set
   * @brief set the @a _currentAnime
   */
  void		setCurrentAnime(std::string const &anime);

  /**
   * @param os the buffer into make variables to save
   * @brief save the object
   */
  virtual void	saveSelf(std::ostream &os) const;

  /**
   * @param screen the sceen
   * @param clock the clock
   * @brief draw the model
   */
  virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock);
  /**
   * @brief the destructor
   */
  virtual ~ModelDraw();
};

/**
 * @brief the geometry draw class
 */
class GeometryDraw : public ADrawComponent
{
protected:
  /**
   * @brief the geometry name
   */
  std::string	_name;

  /**
   * @brief contain the geometry to draw
   */
  DrawComponent	const*	_toDraw;
protected:

  /**
   * @param screen the screen
   * @param pos the position to draw
   * @param transform the transformation to do before draw
   * @brief draw the geometry on the screen
   */
  void		draw_in_screen(Screen::AScreen &screen, glm::vec3 const& pos,
			       glm::mat4 const& transform);
public:
  /**
   * @param str the geometry name
   * @brief the contructor
   */
  GeometryDraw(std::string const& str);

  /**
   * @param c the letter geometry name
   * @brief the contructor
   */
  GeometryDraw(char c);

  /**
   * @param is buffer that contain variables in load
   * @brief load contructor
   */
  GeometryDraw(std::istream & is);

  /**
   * @param os the buffer into make variables to save
   * @brief save the object
   */
  virtual void	saveSelf(std::ostream &os) const;

  /**
   * @param screen the sceen
   * @param clock the clock
   * @brief draw the geometry
   */
  virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock);

  /**
   * @brief the destructor
   */
  virtual ~GeometryDraw() {}

  /**
   * @return @a _toDraw
   * @brief return the @a DrawComponent
   */
  DrawComponent const* getToDraw() {return _toDraw;}
};

#endif /* !MODELDRAW_H_ */
