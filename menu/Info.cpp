#include "Info.hpp"

Info::Info()
  : _nplayers(2), _nai(2), _mapX(15), _mapY(15), _free(50), _unde(50),
    _realFree(50), _realUnde(50), _mod(NONE), _savefile(""), _perfectMaze(0)
{}

Info::~Info()
{}
