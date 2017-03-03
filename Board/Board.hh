#ifndef BOARD_H_
# define BOARD_H_

# include <vector>
# include <string>
# include "Part.hh"
# include "IObject.hh"
# include "Mutex.hh"

class Entity;

/**
 ** @class Board
 ** @brief this is used to store all the entities during the party
 */
class Board : public IObject
{
private:
  size_t	_width;
  size_t	_height;
  size_t	_colparts;
  size_t	_rowparts;
  std::vector<Part*>	_parts;
  CThread::Mutex	_mutex;
  std::list<Entity*>	_toUpdate;
  std::stack<Entity*>	_toRemove;
private:
  Board(Board const &);
  Board operator=(Board const&);
private:
  /**
   ** @class PartCreator
   ** @brief a private functor in board
   */
  class		PartCreator
  {
    CThread::Mutex *_mutex;
  public:
    PartCreator(CThread::Mutex *);
    void	operator()(Part *&);
  };
public:
  Board(size_t width, size_t height);
  Board(std::string const & mapfile);
  void		update();
  /**
   ** @param toadd the entity to be added
   ** @return whether or not if it is added
   ** @brief Try to add an entity
   */
  bool		addEntity(Entity *toadd);
  Part		*find_part(glm::vec3 const& pos) const;
  virtual	~Board();
public:
  void			removeEntity(Entity *e);
  CThread::Mutex	&getMutex() {return _mutex;}
  Entity*		findBlock(glm::vec3 const&);
  virtual int		update(gdl::Clock const &, gdl::Input &);
  virtual void		draw(Screen::AScreen &, gdl::Clock const &);
  size_t		getWidth() const;
  size_t		getHeight() const;
  std::vector<Part *> const & getParts() const;
  void			clear();
  void			flush();
  void			saveSelf(std::ostream &);
};

#endif /* !BOARD_H_ */
