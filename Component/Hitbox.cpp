#include "Hitbox.hh"
#include "Position.hh"
#include "Entity.hpp"
#include <iostream>
#include "SaveLoad.hh"

Hitbox::Hitbox(std::istream &is)
{
  SaveLoad::loadVec3(is, _size);
}


void	Hitbox::saveSelf(std::ostream &os) const
{
  os << "Hitbox ";
  SaveLoad::saveVec3(os, _size);
  os << std::endl;
}

bool	Hitbox::isInRange(glm::vec3 const& pos) const
{
  if (pos.z <= _size.z / 2.0 && pos.z > _size.z / -2.0)
    {
      if (pos.x <= _size.x / 2.0 && pos.x > _size.x / -2.0)
	return (true);
    }
  return (false);
}

bool	Hitbox::isInTouch(Hitbox const& target) const
{
  Position		*self;
  Position		*op;
  glm::vec3 const&	ops(target.getSize());

  self = _owner->getComponent<Position>();
  if (self && (op = (target.getOwner())->getComponent<Position>()))
    {
      glm::vec3 const	relative(op->getPos() - self->getPos());

      return (target.isInRange(glm::vec3(relative.x - _size.x / 2.0f, 0,
					 relative.z - _size.z / 2.0f))
	      || target.isInRange(glm::vec3(relative.x + _size.x / 2.0f, 0,
					    relative.z - _size.z / 2.0f))
	      || target.isInRange(glm::vec3(relative.x + _size.x / 2.0f, 0,
					    relative.z + _size.z / 2.0f))
	      || target.isInRange(glm::vec3(relative.x - _size.x / 2.0f, 0,
					    relative.z + _size.z / 2.0f))
	      || isInRange(glm::vec3(relative.x - ops.x / 2.0f, 0,
					 relative.z - ops.z / 2.0f))
	      || isInRange(glm::vec3(relative.x + ops.x / 2.0f, 0,
					    relative.z - ops.z / 2.0f))
	      || isInRange(glm::vec3(relative.x + ops.x / 2.0f, 0,
					    relative.z + ops.z / 2.0f))
	      || isInRange(glm::vec3(relative.x - ops.x / 2.0f, 0,
					    relative.z + ops.z / 2.0f)));
    }
  return (false);
}
