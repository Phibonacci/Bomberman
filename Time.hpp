#ifndef TIME_H_
# define TIME_H_

#include <string>

/**
 **@namespace CTime
 **@brief Time management as its finest
 */
namespace CTime
{
  #include <ctime>

  /**
   **@class Time
   **@brief Just here to get the time!
   */
  class	Time
  {
  public:

    /**
     **@fn getCurrentTime
     **@brief gets the... time.
     */
    static std::string	getCurrentTime()
    {
      time_t		t;

      time(&t);
      return (ctime(&t));
    }
  };
}

#endif /* !TIME_H_ */
