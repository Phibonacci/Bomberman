#include "GameIA.hh"
#include "AI.hh"
#include "utils.hh"
#include "Player.hh"
#include "Destruction.hh"
#include "Bonus.hh"
#include "HasPlayer.hh"
#include "CanKick.hh"
#include "BombMake.hh"

int	Controller::AI::getPosition(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  glm::vec2 const & position = self->_player->getPosition();
  lua_pushnumber(l, position.x);
  lua_pushnumber(l, position.y);
  return 2;
}

int	Controller::AI::getMapSize(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  lua_pushinteger(l, (*self->_map)[0].size());
  lua_pushinteger(l, self->_map->size());
  return 2;
}

int	Controller::AI::setDirection(lua_State *l) {
  AI *s = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));
  float speed = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  float	angle = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  s->_dir.setAngle(angle);
  if (speed > 1)
    speed = 1.0;
  else if (speed < 0)
    speed = 0.0;
  s->_dir.setSpeed(speed);
  return 0;
}

int	Controller::AI::putBomb(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  self->_button = BUTTON_PUTBOMB;
  return 0;
}

int	Controller::AI::noButton(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  self->_button = BUTTON_INVALID;
  return 0;
}

int	Controller::AI::getAngle(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));
  float const & angle = self->_dir.getAngle();

  lua_pushnumber(l, angle);
  return 1;
}

bool	Controller::AI::amExposedAux(AI *self, size_t x, size_t y) {
  if ((*self->_map)[y][x] == GameIA::DANGER
      || (*self->_map)[y][x] == GameIA::BOMB
      || (*self->_map)[y][x] == GameIA::FIRE)
    return true;
  return false;
}

int	Controller::AI::amExposed(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  float	x = self->_player->getPosition().x;
  float	y = self->_player->getPosition().y;
  size_t sx_1 = static_cast<size_t>(x + 0.5 - 0.3);
  size_t sy_1 = static_cast<size_t>(y + 0.5 - 0.3);
  size_t sx_2 = static_cast<size_t>(x + 0.5 + 0.3);
  size_t sy_2 = static_cast<size_t>(y + 0.5 + 0.3);

  if (amExposedAux(self, sx_1, sy_1) == true
      || amExposedAux(self, sx_2, sy_1) == true
      || amExposedAux(self, sx_1, sy_2) == true
      || amExposedAux(self, sx_2, sy_2) == true) {
    lua_pushinteger(l, 1);
    return 1;
  }
  lua_pushinteger(l, 0);
  return 1;
}

int	Controller::AI::dangerAround(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  float	x = self->_player->getPosition().x;
  float	y = self->_player->getPosition().y;
  size_t sx = static_cast<size_t>(x + 0.5);
  size_t sy = static_cast<size_t>(y + 0.5);

  if (amExposedAux(self, sx, sy - 1) == true
      || amExposedAux(self, sx, sy + 1) == true
      || amExposedAux(self, sx - 1, sy) == true
      || amExposedAux(self, sx + 1, sy) == true
      || amExposedAux(self, sx + 1, sy + 1) == true
      || amExposedAux(self, sx + 1, sy - 1) == true
      || amExposedAux(self, sx - 1, sy + 1) == true
      || amExposedAux(self, sx - 1, sy - 1) == true
      || amExposedAux(self, sx, sy) == true) {
    lua_pushinteger(l, 1);
    return 1;
  }
  lua_pushinteger(l, 0);
  return 1;
}

int	Controller::AI::isExposed(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));
  float	y = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  float	x = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  size_t sx = static_cast<size_t>(x + 0.5);
  size_t sy = static_cast<size_t>(y + 0.5);

  if (sx >= self->_map->getWidth()
      || sy >= self->_map->getHeight()) {
    return 0;
  }
  if (amExposedAux(self, sx, sy) == true) {
    lua_pushinteger(l, 1);
    return 1;
  }
  lua_pushinteger(l, 0);
  return 1;
}

bool	Controller::AI::matchMask(int mask, int mask_in, int mask_out) {
  if ((mask & mask_in) == mask_in && (mask & mask_out) == 0)
    return true;
  return false;
}

static const int g_move[4][2] = {
  {1, 0},
  {-1, 0},
  {0, 1},
  {0, -1}
};

bool	Controller::AI::dijkstraFill(AI *self,
				     std::stack< glm::vec2 > * new_stack,
				     size_t x, size_t y) {

  if (x == 0
      || y == 0
      || x >= self->_map->getWidth() - 1
      || y >= self->_map->getHeight() - 1)
    return false;

  for (size_t i = 0; i < LEN(g_move); i++) {
    int tx = g_move[i][0] + x;
    int ty = g_move[i][1] + y;
    if (self->_dmap[ty][tx] < 0)
      continue;
    if ((self->_dmap[ty][tx] & self->_mask) != 0) {
      self->_path_x = tx;
      self->_path_y = ty;
      return true;
    }
    if (self->_dmap[ty][tx] == GameIA::NONE
	|| self->_dmap[ty][tx] == GameIA::BONUS
	|| (self->_safe == false && self->_dmap[ty][tx] == GameIA::DANGER)) {
      self->_dmap[ty][tx] = self->_id;
      new_stack->push(glm::vec2(tx, ty));
      self->_blocked = false;
    }
  }
  return false;
}

void	Controller::AI::getFirstStep(AI *self) {
  while (self->_id < 0) {
    for (size_t i = 0; i < LEN(g_move); i++) {
      int tx = g_move[i][0] + self->_path_x;
      int ty = g_move[i][1] + self->_path_y;
      if (self->_dmap[ty][tx] == self->_id) {
	self->_path_x = tx;
	self->_path_y = ty;
	break;
      }
    }
    self->_id++;
  }
}


bool	Controller::AI::dijkstra(AI *self, int mask, bool safe) {
  self->_path_x = -1;
  self->_path_y = -1;
  self->_dmap = (*self->_map);
  self->_blocked = false;

  self->_mask = mask;
  self->_safe = safe;
  std::stack< glm::vec2 > * last_id;

  size_t x = static_cast<size_t>(self->_player->getPosition().x + 0.5);
  size_t y = static_cast<size_t>(self->_player->getPosition().y + 0.5);


  if ((self->_dmap[y][x] & self->_mask) != 0) {
    self->_path_x = x;
    self->_path_y = y;
    return true;
  }

  last_id = new std::stack< glm::vec2 >;
  last_id->push(glm::vec2(x, y));

  for (self->_id=-1; self->_blocked == false; self->_id--) {
    self->_blocked = true;
    std::stack< glm::vec2 > * new_stack = new std::stack< glm::vec2 >;
    while (!last_id->empty()) {
      if (dijkstraFill(self, new_stack, last_id->top().x, last_id->top().y) == true)
	{
	  delete new_stack;
	  delete last_id;
	  getFirstStep(self);
	  return true;
	}
      last_id->pop();
    }
    delete last_id;
    last_id = new_stack;
    }
  return false;
}

int	Controller::AI::toBrick(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  if (!dijkstra(self, GameIA::DBLOCK, false)) {
    lua_pushnumber(l, -1);
    lua_pushnumber(l, -1);
    return 2;
  }

  lua_pushnumber(l, self->_path_x);
  lua_pushnumber(l, self->_path_y);
  return 2;
}

int	Controller::AI::toBrickSafe(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  if (!dijkstra(self, GameIA::DBLOCK, true)) {
    lua_pushnumber(l, -1);
    lua_pushnumber(l, -1);
    return 2;
  }

  lua_pushnumber(l, self->_path_x);
  lua_pushnumber(l, self->_path_y);
  return 2;
}

int	Controller::AI::brickAround(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  float	x = self->_player->getPosition().x;
  float	y = self->_player->getPosition().y;
  size_t sx = static_cast<size_t>(x + 0.5);
  size_t sy = static_cast<size_t>(y + 0.5);

  for (size_t i = 0; i < LEN(g_move); i++) {
    if ((*self->_map)[sy + g_move[i][1]][sx + g_move[i][0]] == GameIA::DBLOCK) {
      lua_pushinteger(l, 1);
      return 1;
    }
  }
  lua_pushinteger(l, 0);
  return 1;
}

int	Controller::AI::toBonus(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  if (!dijkstra(self, GameIA::BONUS, false)) {
    lua_pushnumber(l, -1);
    lua_pushnumber(l, -1);
    return 2;
  }

  lua_pushnumber(l, self->_path_x);
  lua_pushnumber(l, self->_path_y);
  return 2;
}

int	Controller::AI::toBonusSafe(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  if (!dijkstra(self, GameIA::BONUS, true)) {
    lua_pushnumber(l, -1);
    lua_pushnumber(l, -1);
    return 2;
  }

  lua_pushnumber(l, self->_path_x);
  lua_pushnumber(l, self->_path_y);
  return 2;
}

int	Controller::AI::safePosition(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));

  size_t x = static_cast<size_t>(self->_player->getPosition().x + 0.5);
  size_t y = static_cast<size_t>(self->_player->getPosition().y + 0.5);

  if ((*self->_map)[y][x] == GameIA::PLAYER) {
    lua_pushnumber(l, x);
    lua_pushnumber(l, y);
    return 2;
  }

  if (!dijkstra(self, GameIA::NONE | GameIA::BONUS, false)) {
    lua_pushnumber(l, -1);
    lua_pushnumber(l, -1);
    return 2;
  }

  lua_pushnumber(l, self->_path_x);
  lua_pushnumber(l, self->_path_y);
  return 2;
}

void	Controller::AI::pushFunction(int (*func)(lua_State *), std::string const & text) {
  lua_pushlightuserdata(_lua_state, this);
  lua_pushcclosure(_lua_state, func, 1);
  lua_setglobal(_lua_state, text.c_str());
}

int	Controller::AI::simpleMoveTo(lua_State *l) {
  AI *self = reinterpret_cast<AI *>(lua_touserdata(l, lua_upvalueindex(1)));
  float to_y = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  float to_x = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  float angle;
  float speed = 1;


  float ox = self->_player->getPosition().x;
  float oy = self->_player->getPosition().y;

  to_x -= ox;
  to_y -= oy;


  angle = atan2(to_x, to_y) - atan2(0, 1);
  angle = angle * 180 / 3.1415926;

  self->_dir.setAngle(angle);
  self->_dir.setSpeed(speed);
  return 0;
}

void	Controller::AI::loadAPI() {
  struct APIFunctions API[] =
    {
      { getPosition, "__getPosition" },
      { getMapSize, "__getMapSize" },
      { setDirection, "__setDirection" },
      { putBomb, "__putBomb" },
      { noButton, "__noButton" },
      { getAngle, "__getAngle" },
      { isExposed, "__isExposed" },
      { amExposed, "__amExposed" },
      { safePosition, "__safePosition" },
      { simpleMoveTo, "__simpleMoveTo" },
      { dangerAround, "__dangerAround" },
      { toBrick, "__toBrick" },
      { toBonus, "__toBonus" },
      { toBrickSafe, "__toBrickSafe" },
      { toBonusSafe, "__toBonusSafe" },
      { brickAround, "__brickAround" }
    };

  for (size_t i = 0; i < LEN(API); i++) {
    pushFunction(API[i].cfunction, API[i].lua_name);
  }
}

void	Controller::AI::loadLibrarys() {
  static const luaL_Reg lib[] = {
    {"base", luaopen_base},
    {"math", luaopen_math},
    {"table", luaopen_table},
    {"bit", luaopen_bit32}
  };

  for (size_t i = 0; i < LEN(lib); i++) {
    luaL_requiref(_lua_state, lib[i].name, lib[i].func, 1);
    lua_settop(_lua_state, 0);
  }
}

void	Controller::AI::loadFile(std::string const & file_name) {
  std::string file_to_load = "./assets/scripts/" + file_name;
  int status = luaL_loadfile(_lua_state, file_to_load.c_str());

  if(status != LUA_OK) {
    std::cerr << "(FAIL)\t\tInvalid AI script" << std::endl;
  }
}

void	Controller::AI::run() {
  int result;

  loadFile(_file_name);
  if ((result = lua_pcall(_lua_state, 0, LUA_MULTRET, 0)) != 0) {
    std:: cerr << "(LUA)\t"
	       << lua_tostring(_lua_state, lua_gettop(_lua_state))
	       << std::endl;
  }
}

void	Controller::AI::checkMove(gdl::Input&) {
  run();
}

PlayerDir const& Controller::AI::getDir() const {
  return (_dir);
}

Controller::Button	Controller::AI::getBut() {
  Button button = _button;
  _button = BUTTON_INVALID;
  return (button);
}

Controller::AI::AI(std::string const & file_name,
		   MapInfo const * map,
		   PlayerInfo const * player)
  : _lua_state(luaL_newstate()),
    _dir(),
    _button(BUTTON_INVALID),
    _map(map),
    _player(player),
    _file_name(file_name),
    _dmap(*map) {
  loadLibrarys();
  loadAPI();
}

Controller::AI::~AI() {
  lua_close(_lua_state);
}
