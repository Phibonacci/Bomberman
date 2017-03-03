#ifndef LOCK_H_
# define LOCK_H_

# include "Mutex.hh"

namespace CThread
{
  /**
   **@class Lock
   **@brief a class of lock and mutex
   */
  class Lock
  {
  public:
    Lock(Mutex &);
    ~Lock();

    /**
     **@fn unLock
     **@brief a function for unlocks
     */
    void	unLock();
  private:
    Lock(const Lock &);
    Lock &operator=(const Lock &);
  private:
    /**
     **@var _mutex
     **@brief well... a mutex, right?
     */
    Mutex	&_mutex;

    /**
     **@var _locked
     **@brief if it's locked or not
     */
    bool	_locked;
  };
}

#endif /* !LOCK_H_ */
