#include "Entity.hpp"
#include "Part.hh"
#include <algorithm>
#include "Lock.hh"

int const	Part::dimension = 5;

int		Part::update(gdl::Clock const &clock, gdl::Input &input)
{
  std::list<Entity*>::iterator tmp;

  tmp = _entities.begin();
  _operating = true;
  while (tmp != _entities.end())
    {
      if ((*tmp)->needDestroy())
	{
	  {
	    CThread::Lock	lockPart(*_mutex);

	    tmp = _entities.erase(tmp);
	  }
	}
      else
	{
	  (*tmp)->update(clock, input);
	  ++tmp;
	}
    }
  _operating = false;
  return (0);
}

void		Part::draw(Screen::AScreen &scr, gdl::Clock const &clock)
{
  std::list<Entity*>::iterator	it = _entities.begin();

  while (it != _entities.end())
    {
      (*it)->draw(scr, clock);
      ++it;
    }
}


static void destroy(Entity *&a)
{
  if (a != NULL)
    {
      delete a;
      a = NULL;
    }
}

Part::~Part()
{
  std::for_each(_entities.begin(),
		_entities.end(), ::destroy);
}

void		Part::removeEntity(Entity *entity)
{
  _toremove.push(entity);
}

void		Part::deleteEntity(Entity *entity)
{
  if (std::find(_todelete.begin(), _todelete.end(), entity)
      == _todelete.end())
    _todelete.push_front(entity);
}

void		Part::addEntity(Entity *entity)
{
  _toadd.push(entity);
}

void		Part::flush()
{
  Entity	*entity;

  while (!_toremove.empty())
    {
      entity = _toremove.top();
      _entities.remove(entity);
      _toremove.pop();
    }
  while (!_toadd.empty())
    {
      entity = _toadd.top();
      _entities.push_front(entity);
      _toadd.pop();
    }
  while (!_todelete.empty())
    {
      entity = *_todelete.begin();
      _entities.remove(entity);
      entity->onDestroy();
      delete entity;
      _todelete.pop_front();
    }
}

void		Part::collide(Entity const *obj, std::list<Entity*> &store) const
{
  std::list<Entity*>::const_iterator	it = _entities.begin();

  while (it != _entities.end())
    {
      if (*it != obj && (obj)->collide(*(*it)))
	{
	  store.push_back(*it);
	}
      ++it;
    }
}

void		Part::collide(Entity const *obj, std::list<Entity*> &store,
			      std::list<Entity*> const &except) const
{
  std::list<Entity*>::const_iterator	it = _entities.begin();

  while (it != _entities.end())
    {
      if (std::find(except.begin(), except.end(), *it) == except.end())
	if (*it != obj && (obj)->collide(*(*it)))
	  {
	    store.push_back(*it);
	  }
      ++it;
    }
}
