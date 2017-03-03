#include <iostream>
#include <algorithm>
#include "Board.hh"
#include "Entity.hpp"
#include "Position.hh"
#include "HasPlayer.hh"
#include "Lock.hh"
#include "EditMake.hpp"

Board::PartCreator::PartCreator(CThread::Mutex *m)
  : _mutex(m)
{
}

void	Board::PartCreator::operator()(Part *&a)
{
  a = new Part(_mutex);
}

Board::Board(size_t width, size_t height)
  : _width(width), _height(height),
    _colparts(width / Part::dimension + !!(width % Part::dimension)),
    _rowparts(height / Part::dimension + !!(height % Part::dimension)),
    _parts(_colparts * _rowparts, NULL)
{
  std::for_each(_parts.begin(), _parts.end(), PartCreator(&_mutex));
}

template <typename T>
static void destroy(T *&a)
{
  delete a;
  a = NULL;
}

Board::~Board()
{
  std::for_each(_parts.begin(), _parts.end(), ::destroy<Part>);
}

void		Board::flush()
{
  while (!_toRemove.empty())
    {
      Entity *e = _toRemove.top();
      Position *pos = e->getComponent<Position>();
      Part	*part;

      if (e->updateNeeded())
	_toUpdate.remove(e);

      if (pos && (part = find_part(pos->getPos())))
	{
	  part->deleteEntity(e);
	}
      _toRemove.pop();
    }
}

void		Board::removeEntity(Entity *e)
{
  _toRemove.push(e);
}

int		Board::update(gdl::Clock const &clock, gdl::Input &input)
{
  {
    std::list<Entity*>::iterator	it = _toUpdate.begin();
    {
      while (it != _toUpdate.end())
  	{
  	  (*it)->update(clock, input);
  	  ++it;
  	}
    }
  }
  flush();
  {
    std::vector<Part*>::const_iterator	it = _parts.begin();

    it = _parts.begin();
    {
      CThread::Lock	lockBoard(_mutex);

      while (it != _parts.end())
	{
	  (*it)->flush();
	  ++it;
	}
    }
  }
  return (0);
}

void		Board::draw(Screen::AScreen &scr, gdl::Clock const &clock)
{
  std::vector<Part*>::iterator	it = _parts.begin();
  size_t		x(0);
  size_t		y(0);

  while (it != _parts.end())
    {
      if (scr.isInAnyScreen(glm::vec3(x + Part::dimension / 2.0f,
				      0, y + Part::dimension / 2.0f),
			    glm::vec3(Part::dimension / 3.0f * 4.0f,
				      0, Part::dimension / 3.0f * 4.0f)))
	(*it)->draw(scr, clock);
      x += Part::dimension;
      if (x >= _width)
      	{
      	  x = 0;
      	  y += Part::dimension;
      	}
      ++it;
    }
}

Part		*Board::find_part(glm::vec3 const &pos) const
{
  size_t		x = static_cast<size_t>(pos.x + 0.5);
  size_t		y = static_cast<size_t>(pos.z + 0.5);

  if (x >= _width || y >= _height || pos.x < 0 || pos.z < 0)
    return (NULL);
  y = y / Part::dimension;
  x = x / Part::dimension;
  return (_parts[y * _colparts + x]);
}


bool		Board::addEntity(Entity *toadd)
{
  Part		*part;
  Position	*pos;

  if ((pos = toadd->getComponent<Position>()) &&
      (part = find_part(pos->getPos())))
    {
      if (toadd->updateNeeded())
	{
	  _toUpdate.push_back(toadd);
	}
      part->addEntity(toadd);
      return (true);
    }
  return (false);
}

size_t		Board::getWidth() const {
  return (_width);
}

size_t		Board::getHeight() const {
  return (_height);
}

std::vector<Part*> const & Board::getParts() const {
  return (_parts);
}

Entity*		Board::findBlock(glm::vec3 const& vec)
{
  Part * part = find_part(vec);
  std::list<Entity*> lentity = part->getEntities();
  for (std::list<Entity*>::iterator it = lentity.begin() ; it != lentity.end() ; it++)
    {
      Position *pos;
      if ((pos = (*it)->getComponent<Position>()) && !(*it)->getComponent<EditMaker>())
	{
	  pos->getPos() = glm::vec3(static_cast<int>(pos->getPos().x + 0.5),
				    static_cast<int>(pos->getPos().y + 0.5),
				    static_cast<int>(pos->getPos().z + 0.5));
	  if (pos->getPos() == vec)
	    {
	      return (*it);
	    }
	}
    }
  return (NULL);
}

void		Board::saveSelf(std::ostream &os)
{
  unsigned int	i;

  os << _width << " " << _height << std::endl;
  {
    CThread::Lock	lockBoard(_mutex);

    i = 0;
    while (i < _parts.size())
      {
	if (_parts[i])
	  _parts[i]->flush();
	++i;
      }
  }
  i = 0;
  while (i < _parts.size())
    {
      if (_parts[i])
	{
	  std::list<Entity*> const & objs((_parts[i])->getEntities());
	  std::list<Entity*>::const_iterator	it = objs.begin();

	  while (it != objs.end())
	    {
	      (*it)->saveSelf(os);
	      ++it;
	    }
	}
      ++i;
    }
}

void		Board::clear()
{
  for (std::vector<Part*>::iterator it = _parts.begin() ; it != _parts.end() ; it++)
    {
      std::list<Entity*> lentity = (*it)->getEntities();
      for (std::list<Entity*>::iterator it2 = lentity.begin()
	     ; it2 != lentity.end() ; it2++)
	{
	  if (!(*it2)->getComponent<HasPlayer>())
	    {
	      Position *pos;

	      if ((pos = (*it2)->getComponent<Position>()))
		{
		  if (pos->getPos().x != 0.0f && pos->getPos().x != _width - 1
		      && pos->getPos().z != 0.0f && pos->getPos().z != _height - 1)
		    removeEntity(*it2);
		}
	    }
	}
    }
}
