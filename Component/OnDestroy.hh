#ifndef ONDESTROY_H_
# define ONDESTROY_H_

# include "AComponent.hh"

/**
 * @brief Interface for destroy checking classes
 */
class	OnDestroy : public AComponent
{
public:
  /**
   * @return true if can be destroy else false
   * @brief check if can be destroy
   */
  virtual bool	canBeDestroy(Entity const&) const = 0;

  /**
   * @return true for destroy else false
   * @brief do an action when the component is destroy
   */
  virtual bool	blockDestroy(Entity const&) const = 0;

  /**
   * @brief the destructor
   */
  virtual ~OnDestroy() {}
};

/**
 * @brief the class for undestructible block
 */
class	Explosimble : public OnDestroy
{
public:
  /**
   * @brief the basic constructor
   */
  Explosimble() {}

  /**
   * @brief the load constructor
   */
  Explosimble(std::istream &) {}

  /**
   * @brief do nothing, return false
   * @return false
   */
  virtual bool	canBeDestroy(Entity const&) const {return (false);}

  /**
   * @brief return false
   * @return false
   */
  virtual bool	blockDestroy(Entity const&) const {return (false);}

  /**
   * @param os buffer to save
   * @brief save the component
   */
  virtual void	saveSelf(std::ostream & os) const;

  /**
   * @brief the destructor
   */
  virtual ~Explosimble() {}
};

/**
 * @brief for the bonus or thing like that
 */
class	Explosible : public OnDestroy
{
public:
  /**
   * @brief the basic constructor
   */
  Explosible() {}

  /**
   * @brief the load constructor
   */
  Explosible(std::istream &) {}

  /**
   * @return true
   * @brief do nothing, return true
   */
  virtual bool	canBeDestroy(Entity const&) const {return (true);}

  /**
   * @return true
   * @brief do nothing, return true
   */
  virtual bool	blockDestroy(Entity const&) const {return (true);}

  /**
   * @param os buffer to save
   * @brief save the component
   */
  virtual void	saveSelf(std::ostream & os) const;

  /**
   * @brief the destructor
   */
  virtual ~Explosible() {}
};

/**
 * @brief for destructible blocks
 */
class	Explosiblock : public OnDestroy
{
public:
  /**
   * @brief the basic constructor
   */
  Explosiblock() {}

  /**
   * @brief the load constructor
   */
  Explosiblock(std::istream &) {}

  /**
   * @return true
   * @brief check if can be destroy
   */
  virtual bool	canBeDestroy(Entity const&) const {return (true);}

  /**
   * @return true if player has piece else false
   * @brief do the stuff before be destroy
   */
  virtual bool	blockDestroy(Entity const&) const;

  /**
   * @param os buffer to save
   * @brief save the component
   */
  virtual void	saveSelf(std::ostream & os) const;

  /**
   * @brief the destructor
   */
  virtual ~Explosiblock() {}
};

/**
 * @brief for players
 */
class	Explosicore : public Explosible
{
  /**
   * @brief the playerScore
   */
  int		_score;
public:
  /**
   * @param score the score
   * @brief the basic constructor
   */
  Explosicore(int score) : _score(score) {}

  /**
   * @brief the load constructor
   */
  Explosicore(std::istream &);

  /*
   * @return true
   * @brief do the stuff before be destroy
   */
  virtual bool	blockDestroy(Entity const&) const;

  /**
   * @param os buffer to save
   * @brief save the component
   */
  virtual void	saveSelf(std::ostream & os) const;

  /**
   * @brief the destructor
   */
  virtual ~Explosicore() {}
};

#endif /* !ONDESTROY_H_ */
