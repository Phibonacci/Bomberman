#include "Lock.hh"

CThread::Lock::Lock(Mutex &mutex)
  : _mutex(mutex), _locked(true)
{
  _mutex.lock();
}

void CThread::Lock::unLock()
{
  if (_locked)
    {
      _locked = false;
      _mutex.unlock();
    }
}

CThread::Lock::~Lock()
{
  if (_locked)
    _mutex.unlock();
}
