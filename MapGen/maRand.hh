#ifndef MARAND_HH_
# define MARAND_HH_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 **@class maRand
 **@brief This class is just a small reencapsulation of the rand() function. It allows the user to change the seed whenever he wants it.
 */
class		maRand
{
private:
  /**
   **@var seed
   **@brief the seed to rulez teh randomz
   */
  int		seed;

public:
  maRand();
  ~maRand();

  /**
   **@fn setSeed
   **@brief this function enables the user to set a ssed for the random generation
   */
  void		setSeed(int _seed);

  /**
   **@fn initSeed
   **@brief this function initialises the seed set before. The program is now ready to random!
   */
  void		initSeed();

  /**
   **@fn getRand
   **@param x is the minimum value in the random segment
   **@param y is the maximum value in the random segment
   **@brief it returns a value between x and y
   */
  int		getRand(int x, int y) const;

  /**
   **@fn getPid
   **@brief small encapsulation of the getpid() function in c, to intesify the randomness. swag
   */
  int		getPid() const;
};

#endif
