/**
 * @file ComponentFactory.hh
 */
#ifndef COMPONENTFACTORY_H_
# define COMPONENTFACTORY_H_

# include "AComponent.hh"
# include <string>
# include <iostream>

/**
 * @class ComponentFactory
 * @brief create a component
 */
class	ComponentFactory
{
  typedef AComponent * (*t_creator)(std::istream &);
  static std::string const	components[];
  static t_creator const	creators[];
public:
  static AComponent *create(std::string const& s, std::istream &is);
};

#endif /* !COMPONENTFACTORY_H_ */
