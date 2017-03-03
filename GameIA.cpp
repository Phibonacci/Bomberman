#include "GameIA.hh"
#include "GameParty.hh"
#include <algorithm>
#include <unistd.h>
#include "Lock.hh"
#include "Entity.hpp"
#include "Position.hh"
#include "Player.hh"
#include "Destruction.hh"
#include "OnDestroy.hh"
#include "Bonus.hh"
#include "HasPlayer.hh"
#include "CanKick.hh"
#include "BombMake.hh"
#include "AI.hh"
#include "utils.hh"
#include "DirReader.hpp"
#include "maRand.hh"

GameIA::GameIA(GameParty *owner)
  : _party(owner), _map(_party->getBoard()->getWidth(),
			_party->getBoard()->getHeight()),
    _needStop(false)
{
  DirReader dir;

  dir.setExtension("lua");
  dir.openFolder("./assets/scripts/");
  dir.genList();
  _files = dir.getFileList();

  refreshMap(_party->getBoard());
}

void	GameIA::stop()
{
  _needStop = true;
}

static void	destroy(PlayerInfo *a) {
  delete a;
}

GameIA::~GameIA()
{
  std::for_each(_players.begin(), _players.end(), ::destroy);
}

void	GameIA::execute()
{
  while (_needStop == false)
    {
      _alive = 0;
      refresh();
      if (_alive == 0)
	break ;
      std::for_each(_players.begin(), _players.end(), CheckMover());
      CThread::Thread::delay(1000);
    }
}

GameIA::BombZone::BombZone(glm::vec3 const & position, int range)
  : _position(position), _range(range) {
}

GameIA::BombZone::~BombZone() {
}

glm::vec3 const &	GameIA::BombZone::getPosition() const {
  return _position;
}

size_t			GameIA::BombZone::getRange() const {
  return _range;
}

void	GameIA::addToMap(int mask, glm::vec3 const & coord) {
  if (_map.getPosition(coord) < mask)
    _map[static_cast<size_t>(coord.z + 0.5)][static_cast<size_t>(coord.x + 0.5)] = mask;
}

int	GameIA::getCase(glm::vec3 const & coord) {
  return _map[static_cast<size_t>(coord.z + 0.5)][static_cast<size_t>(coord.x + 0.5)];
}

void	GameIA::putBomb(Entity const * entity, glm::vec3 const & coord) {
  BombExplode *e;

  if ((e = entity->getComponent<BombExplode>())) {
    addToMap(BOMB, coord);
    unsigned int range = e->getRange();
    BombZone * bomb = new BombZone(coord, range);
    _bombstack.push(bomb);
  }
}

void	GameIA::putFire(Entity const * entity, glm::vec3 const & coord) {
  OnTouchFire *e;

  if ((e = entity->getComponent<OnTouchFire>())) {
    addToMap(FIRE, coord);
  }
}
void	GameIA::putBonus(Entity const * entity, glm::vec3 const & coord) {
  OnTouchCollect *e;

  if ((e = entity->getComponent<OnTouchCollect>())) {
    addToMap(BONUS, coord);
  }
}

void	GameIA::putBlock(Entity const * entity, glm::vec3 const & coord) {
  if (entity->getComponent<OnTouchBlock>()) {
    if (entity->getComponent<Explosimble>())
      addToMap(SBLOCK, coord);
    else
      addToMap(DBLOCK, coord);
  }
}

void	GameIA::putPlayer(Entity const * entity, glm::vec3 const & coord) {
  if (entity->getComponent<BombMaker>()) {
    addToMap(PLAYER, coord);
  }
}

void	GameIA::refreshMap(Board *board) {
  for (size_t j = 0; j < board->getHeight(); j++) {
    for (size_t i = 0; i < board->getWidth(); i++) {
      _map[j][i] = NONE;
    }
  }

  std::vector<Part*> const & parts = board->getParts();
  for (std::vector<Part*>::const_iterator it_board = parts.begin();
       it_board != parts.end();
       it_board++) {
    (*it_board)->flush();
    std::list<Entity*> const & entities = (*it_board)->getEntities();
    for (std::list<Entity*>::const_iterator it_part = entities.begin();
	 it_part != entities.end();
	 it_part++) {
      Position const *pos = (*it_part)->getComponent<Position>();
      if (pos != NULL) {
	glm::vec3 const & coord = pos->getPos();
	putBomb(*it_part, coord);
	putFire(*it_part, coord);
	putBonus(*it_part, coord);
	putBlock(*it_part, coord);
	putPlayer(*it_part, coord);
      }
    }
  }
}

void	GameIA::addBombZone(size_t width, size_t height) {
  while (!_bombstack.empty()) {
    glm::vec3 const & position =_bombstack.top()->getPosition();
    size_t	x = position.x;
    size_t	y = position.z;
    int		range = _bombstack.top()->getRange();
    int		tmp_range = range;

    tmp_range = range;
    for (size_t i = x; i < width - 1 && tmp_range >= 0
	   && (_map[y][i] > DBLOCK || _map[y][i] == NONE); i++) {
      if (_map[y][i] < DANGER)
	_map[y][i] = DANGER;
      tmp_range--;
    }
    tmp_range = range;
    for (size_t i = x; i > 0 && i < width - 1 && tmp_range >= 0
	   && (_map[y][i] > DBLOCK || _map[y][i] == NONE); i--) {
      if (_map[y][i] < DANGER)
	_map[y][i] = DANGER;
      tmp_range--;
    }
    tmp_range = range;
    for (size_t i = y; i < height - 1 && tmp_range >= 0
	   && (_map[i][x] > DBLOCK || _map[i][x] == NONE); i++) {
      if (_map[i][x] < DANGER)
	_map[i][x] = DANGER;
      tmp_range--;
    }
    tmp_range = range;
    for (size_t i = y; i > 0 && i < height - 1 && tmp_range >= 0
	   && (_map[i][x] > DBLOCK || _map[i][x] == NONE); i--) {
      if (_map[i][x] < DANGER)
	_map[i][x] = DANGER;
      tmp_range--;
    }
    delete _bombstack.top();
    _bombstack.pop();
  }
}

void	GameIA::clearZone(glm::vec3 const & coord) {
  for (int y = coord.z - Part::dimension + 1;
       y < static_cast<int>(_map.getHeight()) - 1
	 && y < coord.z + Part::dimension;
       y++) {
    for (int x = coord.x - Part::dimension + 1;
	 y > 0 && x < static_cast<int>(_map.getWidth()) - 1
	   && x < coord.x + Part::dimension;
	 x++) {
      if (x > 0)
	_map[y][x] = NONE;
    }
  }
}

static int const	positions[][2] = {
  {0, 0},
  {0, Part::dimension},
  {0, -Part::dimension},
  {Part::dimension, 0},
  {Part::dimension, Part::dimension},
  {Part::dimension, -Part::dimension},
  {-Part::dimension, 0},
  {-Part::dimension, Part::dimension},
  {-Part::dimension, -Part::dimension}
};

void	GameIA::selectParts(Board *board) {
  _parts.clear();
  for (std::vector< PlayerInfo * >::const_iterator it = _players.begin();
       it != _players.end();
       it++) {
    size_t x = (*it)->getPosition().x;
    size_t y = (*it)->getPosition().y;
    Part * p;

    for (size_t i = 0; i < LEN(positions); i++) {
      p = board->find_part(glm::vec3(x + positions[i][0], 0, y + positions[i][1]));
      if (p && std::find(_parts.begin(), _parts.end(), p) == _parts.end())
	_parts.push_back(p);
    }
    clearZone(glm::vec3(x, 0, y));
  }
}

void	GameIA::refreshParts(Board *board) {
  for (std::list<Part*>::const_iterator it_board = _parts.begin();
       it_board != _parts.end();
       it_board++) {
    CThread::Lock lockBoard(board->getMutex());
    std::list<Entity*> const & entities = (*it_board)->getEntities();
    for (std::list<Entity*>::const_iterator it_part = entities.begin();
	 it_part != entities.end();
	 it_part++) {
      Position const *pos = (*it_part)->getComponent<Position>();
      if (pos != NULL) {
	glm::vec3 const & coord = pos->getPos();

	putBomb(*it_part, coord);
	putFire(*it_part, coord);
	putBonus(*it_part, coord);
	putBlock(*it_part, coord);
	putPlayer(*it_part, coord);
      }
    }
  }

}

void	GameIA::refresh() {
  Board *board = _party->getBoard();

  for (std::vector< PlayerInfo * >::iterator it = _players.begin();
       it != _players.end();
       it++) {
    CThread::Lock lockBoard(board->getMutex());
    _alive += (*it)->positionUpdate();
  }
  if (board)
    {
      selectParts(board);
      refreshParts(board);
      addBombZone(board->getWidth(), board->getHeight());
    }
}

GameIA::CheckMover::CheckMover()
  : _alive(0)
{}

void GameIA::CheckMover::operator()(PlayerInfo *t)
{
  _alive += t->updateIA();
}

bool		PlayerInfo::updateIA()
{
  _AI->run();
  return (true);
}

bool		PlayerInfo::positionUpdate() {
  Entity	*e;
  Position	*pos;

  if ((e = _player->getPerson()) &&
      (pos = e->getComponent<Position>()))
    {
      _position.x = pos->getPos().x;
      _position.y = pos->getPos().z;
      return true;
    }
  return false;
}

void	PlayerInfo::setIA(Controller::AI *a)
{
  _AI = a;
}

Controller::AI	*GameIA::addNewIA(Player const *pl)
{
  Controller::AI	*rt;
  maRand rand;

  PlayerInfo * pinfo = new PlayerInfo(NULL, pl);

  rand.initSeed();
  int	i = rand.getRand(0, _files.size());
  rt = new Controller::AI(_files[i], &_map, pinfo);
  pinfo->setIA(rt);
  _players.push_back(pinfo);
  return (rt);
}

PlayerInfo::PlayerInfo(Controller::AI * AI, Player const * player)
  : _AI(AI), _player(player), _position(glm::vec2(0, 0)) {
}

glm::vec2 const & PlayerInfo::getPosition() const {
  return _position;
}

int	MapInfo::getPosition(glm::vec3 const & coord) const {
  return (*this)[static_cast<size_t>(coord.z + 0.5)][static_cast<size_t>(coord.x + 0.5)];
}

size_t	MapInfo::getWidth() const {
  return (*this)[0].size();
}

size_t	MapInfo::getHeight() const {
  return (*this).size();
}

MapInfo::MapInfo(int width, int height)
  : std::vector< std::vector <int> >(height, std::vector< int >(width, 0)) {
}

MapInfo::~MapInfo()
{}

PlayerInfo::~PlayerInfo()
{}
