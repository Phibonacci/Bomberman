/**
 * @file LifeTimer.hh
 */
#ifndef LIFETIMER_H_
# define LIFETIMER_H_

# include "AComponent.hh"

/**
 * @brief the life timer class Entity die after some time
 */
class	LifeTimer : public AUpdateComponent
{
protected:
  /**
   * @brief time remaining before dead
   */
  float	_timeRest;
public:
  /**
   * @param time the time before be destroy
   * @brief the basic contructor
   */
  LifeTimer(float time) : _timeRest(time) {}

  /**
   * @brief the load constructor
   */
  LifeTimer(std::istream & is) { is >> _timeRest;}

  /**
   * @brief the class save
   */
  virtual void	saveSelf(std::ostream &os) const;

  /**
   * @brief update the @a _timeRest
   */
  virtual void	update(gdl::Clock const &clock, gdl::Input &);

  /**
   * @brief the destructor
   */
  virtual ~LifeTimer() {}
};

#endif /* !LIFETIMER_H_ */
