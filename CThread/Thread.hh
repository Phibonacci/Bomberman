#ifndef THREAD_H_
# define THREAD_H_

#include <pthread.h>

/**
 **@namespace CThread
 **@brief all you need in order to use the threads safely
 */
namespace CThread
{
  /**
   **@class IThreadObj
   **@brief an interface to rule the threads and their use
   */
  class IThreadObj
  {
  public:
    virtual void	execute() = 0;
    virtual	~IThreadObj(){}
  };

  /**
   **@class Thread
   **@brief a class to deal with the threads
   */
  class Thread
  {
  public:
    Thread(IThreadObj *obj);
    ~Thread();
  private:
    /**
     **@fn runThread
     **@brief to run the thread, go there
     */
    static void	*runThread(void *);
  public:

    /**
     **@fn terminate
     **@brief t terminate a thread, go here
     */
    void	terminate();

    /**
     **@fn wait
     **@brief to wait, please go there
     */
    void	wait();

    /**
     **@fn delay
     **@brief a function that helps the thread to delay
     */
    static void		delay(unsigned int);
  private:
    Thread(const Thread &);
    Thread &operator=(const Thread &);
  private:
    /**
     **@var _toRun
     **@brief an object to use the threads
     */
    IThreadObj		*_toRun;

    /**
     **@var _notStopped
     **@brief a bool to know if it's stopped or not
     */
    bool		_notStopped;

    /**
     **@var _id_thread
     **brief the pthread himself
     */
    pthread_t		_id_thread;
  };
};

#endif /* !THREAD_H_ */
