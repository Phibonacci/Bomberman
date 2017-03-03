#include "Mutex.hh"
#include "Except.hpp"

CThread::Mutex::Mutex()
{
  if (pthread_mutex_init(&_mutex, NULL))
    throw BombermanException("Not enough resources");
}

void	CThread::Mutex::lock()
{
  if (pthread_mutex_lock(&_mutex))
    throw BombermanException("Fatal error lock mutex");
}

void	CThread::Mutex::unlock()
{
  if (pthread_mutex_unlock(&_mutex))
    throw BombermanException("Fatal error unlock mutex");
}

CThread::Mutex::~Mutex()
{
  pthread_mutex_destroy(&_mutex);
}
