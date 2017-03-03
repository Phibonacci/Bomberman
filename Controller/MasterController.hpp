#ifndef __MASTERCONTROLLER_HPP__
# define __MASTERCONTROLLER_HPP__

# include "Peripheral.hh"
# include <vector>

namespace Controller
{
  /**
   * @class MasterController
   * @brief initialize the @a Controllers
   */
  class MasterController
  {
    /**
     * @var _cuse
     * @brief the controller which's using at the moment
     */
    static size_t			_cuse;

    /**
     * @var _cmax
     * @brief the maximum number of controller
     */
    static size_t			_cmax;

    /**
     * @var _tabPeriph
     * @brief a vector which contain controllers
     */
    static std::vector<Peripheral*>	_tabPeriph;

  public:
    /**
     * @fn initialize
     * @brief create the controllers
     */
    static void		initialize();

    /**
     * @fn rtPeripheral
     * @brief return the next peripheral no use then increment _cuse
     * @return the next peripheral no use or NULL if  _cuse == _cmax
     */
    static Peripheral*	rtPeripheral();

    /**
     * @fn restart
     * @brief make @a _cuse to 0
     */
    static void		restart();

    /**
     * @fn getNController
     * @brief return @a _cmax the number of controller
     * @return @a _cmax
     */
    static int		getNController();
  };
};

#endif // !__MASTERCONTROLLER_HPP__
