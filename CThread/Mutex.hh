#ifndef MUTEX_H_
# define MUTEX_H_

# include <pthread.h>

namespace CThread
{
  /**
   **@class Mutex
   **@brief a mutex to rule them all
   */
  class Mutex
  {
  public:
    Mutex();
    ~Mutex();

    /**
     **@fn lock
     **@brief to lock the mutex
     */
    void	lock();

    /**
     **@fn unlock
     **@brief to unlock the mutex
     */
    void	unlock();
  private:
    Mutex(const Mutex &);
    Mutex &operator=(const Mutex &);
  private:
    /**
    **@var _mutex
    **@brief a mutex to be locked
    */
    pthread_mutex_t	_mutex;

    /**
     **@var _locked
     **@brief to know if it's locked or not
     */
    bool		_locked;
  };
}

#endif /* !MUTEX_H_ */
