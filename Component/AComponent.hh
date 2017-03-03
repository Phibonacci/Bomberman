/**
 * @file AComponent.hh
 */
#ifndef ACOMPONENT_H_
# define ACOMPONENT_H_

# include <SdlContext.hh>
# include <BasicShader.hh>
# include <iostream>
# include <istream>
# include "AScreen.hh"

class Entity;

/**
 * @class AComponent
 * @brief An abstract class for Components
 */
class	AComponent
{
protected:
  Entity	*_owner;
public:
  AComponent() : _owner(NULL) {}
  virtual void	setOwner(Entity *owner) {_owner = owner;}
  Entity *getOwner() const {return _owner;}
  virtual ~AComponent() {}
  virtual void	saveSelf(std::ostream&) const = 0;
};

/**
 * @class AUpdateComponent
 * @brief An update needed component
 */
class	AUpdateComponent : public AComponent
{
public:
  virtual void update(gdl::Clock const &clock, gdl::Input &input) = 0;
  virtual ~AUpdateComponent() {}
};

/**
 * @class ADrawComponent
 * @brief An draw needed component
 */
class	ADrawComponent : public AComponent
{
public:
  virtual void draw(Screen::AScreen &screen, gdl::Clock const &clock) = 0;
  virtual ~ADrawComponent() {}
};

#endif /* !ACOMPONENT_H_ */
