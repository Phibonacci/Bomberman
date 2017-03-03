#include <pthread.h>
#include "Thread.hh"
#include "Except.hpp"
#include <signal.h>
#include <unistd.h>

void *CThread::Thread::runThread(void * arg)
{
  IThreadObj *r = reinterpret_cast<IThreadObj*>(arg);

  r->execute();
  return (r);
}

CThread::Thread::Thread(CThread::IThreadObj *r)
  : _toRun(r), _notStopped(true)
{
  if (pthread_create(&_id_thread, NULL, &runThread, _toRun))
    throw BombermanException("Cant thread");
}

void CThread::Thread::wait()
{
  if (_notStopped)
    pthread_join(_id_thread, NULL);
  _notStopped = false;
}

void CThread::Thread::terminate()
{
  pthread_kill(_id_thread, SIGINT);
}

CThread::Thread::~Thread()
{
  if (_notStopped)
    pthread_join(_id_thread, NULL);
  _notStopped = false;
}

void CThread::Thread::delay(unsigned int time)
{
  usleep(time);
}
