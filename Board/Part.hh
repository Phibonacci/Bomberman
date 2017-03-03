#ifndef PART_H_
# define PART_H_

# include <string>
# include <list>
# include <SdlContext.hh>
# include <glm/glm.hpp>
# include <stack>

# include "IObject.hh"
# include "Mutex.hh"

class Entity;

/**
 ** @brief This class represents a displayable item
 */
class Part : public IObject
{
private:
  std::list<Entity*>	_entities;
  bool			_operating;
  std::stack<Entity*>	_toremove;
  std::stack<Entity*>	_toadd;
  std::list<Entity*>	_todelete;
  CThread::Mutex	*_mutex;
private:
  Part(Part const&);
  Part& operator=(Part const&);
public:
  static int const	dimension;
  Part(CThread::Mutex *mutex) : _entities(), _mutex(mutex) {}
  ~Part();
  std::list<Entity*> &		getEntities() {return _entities;}
  std::list<Entity*> const &	getEntities() const {return _entities;}
public:

  /**
   ** This function checks all the states of a part
   ** @param clock
   ** @param input
   */
  virtual int	update(gdl::Clock const &clock, gdl::Input &input);

  /**
   ** This functions draws the model on the screen
   ** @param screen
   ** @param clock
   */
  virtual void	draw(Screen::AScreen &screen, gdl::Clock const &clock);

  /**
   ** This function removes an entity
   ** @param entity
   */
  void		removeEntity(Entity *entity);

  /**
   ** This function adds an entity
   ** @param entity
   */
  void		addEntity(Entity *entity);

  /**
   ** This function deletes an entity
   ** @param entity
   */
  void		deleteEntity(Entity *entity);

  /**
   ** This functions checks collision between an object and other objects but excludes some
   ** @param obj
   ** @param store
   */
  void		collide(Entity const *obj,
  			std::list<Entity*> &store) const;

  /**
   ** This functions checks collision between an object and other objects but excludes some
   ** @param obj
   ** @param store
   ** @param except
   */
  void		collide(Entity const *obj,
  			std::list<Entity*> &store,
  			std::list<Entity*> const &except) const;
  /**
   ** This functions renders the item
   */
  void		flush();
};

#endif /* !PART_H_ */
