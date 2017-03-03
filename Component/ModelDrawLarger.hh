#ifndef MODELDRAWLARGER_H_
# define MODELDRAWLARGER_H_

# include "ModelDraw.hh"

/**
 * @brief the size of the model
 */
class ModelDrawLarger : public ModelDraw
{
private:
  /**
   * @brief the model ratio
   */
  float		_largeRatio;

  /**
   * @brief the model state
   */
  bool		_state;

public:
  /**
   * @brief the constructor
   */
  ModelDrawLarger(std::string const& str, float a) : ModelDraw(str), _largeRatio(a) {_state = false;}
  /**
   * @brief draw the model
   */
  virtual void	draw(Screen::AScreen &, gdl::Clock const&);

  /**
   * @brief the desctructor
   */
  virtual ~ModelDrawLarger() {}
};

#endif /* !MODELDRAWLARGER_H_ */
