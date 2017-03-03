#ifndef DIRECTION_H_
# define DIRECTION_H_

/**
 * @class Direction
 * @brief convert enum to cartesian values
 */
class	Direction
{
public:
  /**
   * @enum t
   * @brief the directions
   */
  enum	t
    {
      UP,
      LEFT,
      RIGHT,
      DOWN
    };
  /**
   * @var all
   * @brief all the directions
   */
  static enum t const		all[4];
  /**
   * @return dx / dy
   * @brief Convert type @a t to dx dy
   */
  static int const *		convert_to_cartesian(enum t t);
};

#endif /* !DIRECTION_H_ */
