/**
 * @file Entity.hpp
 */
#ifndef ENTITY_H_
# define ENTITY_H_

# include <list>
# include <algorithm>
# include "AComponent.hh"
# include "IObject.hh"
# include <iostream>

template<class T, class U>
inline bool type_match(U *target)
{
  return ((dynamic_cast<T*>(target)) != NULL);
}

template<class T>
inline void type_delete(T *&target)
{
  delete target;
  target = NULL;
}

/**
 * @class Entity
 * @brief A Component Container, an object drawable and updateable
 */
class Entity : public IObject
{
  bool				_needDestroy;
  std::list<AComponent*>	_components;
  std::list<AUpdateComponent*>	_toupdate;
  std::list<ADrawComponent*>	_todraw;
private:
  Entity(Entity const&);
  Entity & operator=(Entity const&);
private:

  /**
   ** @brief This class is used to update the components properties
   */
  class		Updator
  {
    gdl::Clock const &_clock;
    gdl::Input &_input;
  public:
    /**
     ** Basic constructor for Updator
     */
    Updator(gdl::Clock const &clock, gdl::Input &input) :
      _clock(clock), _input(input) {}
    /**
     ** Operator () overload, used to update a component
     ** @param target
     */
    void	operator()(AUpdateComponent *target) {
      target->update(_clock, _input);
    }
  };

  /**
   ** @brief This class draw models on screen
   */
  class		Drawer
  {
    Screen::AScreen &_screen;
    gdl::Clock const &_clock;
  public:

    /**
     ** Basic constructor for Drawer class
     ** @param screen
     ** @param clock
     */
    Drawer(Screen::AScreen &screen, gdl::Clock const &clock) :
      _screen(screen), _clock(clock) {}

    /**
     ** Operator () overload, used to render a component
     ** @param target
     */
    void	operator()(ADrawComponent *target) {
      target->draw(_screen, _clock);
    }
  };

  /**
   ** @brief Saver class is a serializer for the components
   */
  class		Saver
  {
    std::ostream	&_os;
  public:
    /**
     ** Basic Saver constructor
     ** @param os
     */
    Saver(std::ostream &os) : _os(os) {}

    /**
     ** Operator () overload, used to save a component
     ** @param target
     */
    void	operator()(AComponent *target);
  };

public:
  Entity() : _needDestroy(false) {}
  Entity(std::istream &);
  template<typename T>
  T	*getComponent() const
  {
    std::list<AComponent*>::const_iterator it;

    if ((it = std::find_if(_components.begin(),
			   _components.end(),
			   ::type_match<T, AComponent>))
	!= _components.end())
      return (static_cast<T*>(*it));
    return (NULL);
  }
  template<typename T>
  Entity&	removeComponent()
  {
    std::list<AComponent*>::iterator it;

    if ((it = std::find_if(_components.begin(),
			   _components.end(),
			   ::type_match<T, AComponent>))
	!= _components.end())
      {
	_toupdate.remove(static_cast<AUpdateComponent*>(*it));
	_todraw.remove(static_cast<ADrawComponent*>(*it));
	delete (*it);
	_components.erase(it);
      }
    return (*this);
  }
  Entity&	removeComponent(AComponent *it)
  {
    _components.remove(it);
    _toupdate.remove(static_cast<AUpdateComponent*>(it));
    _todraw.remove(static_cast<ADrawComponent*>(it));
    return (*this);
  }
  Entity&	addComponent(AComponent *compo);
  virtual int update(gdl::Clock const &clock, gdl::Input &input)
  {
    std::for_each(_toupdate.begin(), _toupdate.end(), Updator(clock, input));
    return (0);
  }
  virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock)
  {
    std::for_each(_todraw.begin(), _todraw.end(), Drawer(screen, clock));
  }
  void		setDestroyed();
  bool		needDestroy() const {return _needDestroy;}
  /**
   * @fn updateNeeded
   * @brief Detect whether or not the entity need to be update
   */
  bool		updateNeeded() const
  {
    return !_toupdate.empty();
  }
  /**
   * @fn collide
   * @brief an alias to finding the hitbox and collide
   */
  bool		collide(Entity const&) const;
  /**
   * @fn onDestroy
   * @brief an alias on finding the Destroy and destroy
   */
  void		onDestroy();
  /**
   * @fn saveSelf
   * @brief to serialize the Entity for save
   */
  void		saveSelf(std::ostream &os);
  ~Entity()
  {
    std::for_each(_components.begin(), _components.end(), ::type_delete<AComponent>);
  }
};

#endif /* !ENTITY_H_ */
