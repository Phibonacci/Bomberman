#ifndef EXCEPT_HPP
# define EXCEPT_HPP

# include <stdexcept>

/**
 ** @brief a basic exception class for the bomberman
 */
class BombermanException : public std::runtime_error
{
public:
  BombermanException(std::string const &e) throw() : std::runtime_error(e){}
  virtual ~BombermanException() throw() {}
};

/**
 ** @brief a basic exception class for map generation
 */
class ExceptMap : public BombermanException
{
public:
  ExceptMap(std::string const & error) throw() : BombermanException(error) {}
  virtual ~ExceptMap() throw() {}
};

/**
 ** @brief a basic exception class for the party
 */
class ExceptParty : public BombermanException
{
public:
  ExceptParty(std::string const & error) throw() : BombermanException(error) {}
  virtual ~ExceptParty() throw() {}
};

/**
 ** @brief a basic exception class for controller handling
 */
class ExceptController : public BombermanException
{
public:
  ExceptController() throw() : BombermanException("Controller error") {}
  virtual ~ExceptController() throw() {}
};

/**
 ** @brief a basic exception class for sound
 */
class ExceptSound : public BombermanException
{
public:
  ExceptSound() throw() : BombermanException("Sound error") {}
  virtual ~ExceptSound() throw() {}
};

#endif
