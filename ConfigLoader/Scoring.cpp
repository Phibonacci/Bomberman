#include <sstream>
#include "Scoring.hpp"
#include <stdlib.h>

int Scoring::_max;
bool Scoring::_init;

Scoring::Scoring()
{
}

Scoring::~Scoring()
{
}

void Scoring::initialize(int max)
{
  if (_init)
    return ;
  _init = true;
  _max = max;
  if (!ConfigLoader::fileExists("Score.txt"))
    {
      int	count;

      count = 1;
      ConfigLoader::appendFile("Score");
      while (count < _max + 1)
	{
	  addScoreLine(count);
	  ++count;
	}
      ConfigLoader::writeToFile("Score.txt", "Score");
    }
  else
    ConfigLoader::parseConfigFile("Score.txt", "Score");
}

void Scoring::addScoreLine(int count)
{
  std::stringstream s[2];

  s[0] << "best_score_" << count;
  s[1] << "best_player_" << count;
  ConfigLoader::appendValues("Score", s[0].str(), ConfigLoader::Value::INT, "0");
  ConfigLoader::appendValues("Score", s[1].str(), ConfigLoader::Value::STRING, "Empty");
}

void Scoring::modifyValue(int count, const std::string &name, int score)
{
  std::stringstream f[2];

  f[0] << "best_player_" << count;
  f[1] << "best_score_" << count;
  ConfigLoader::modifyValue("Score", f[0].str(), name);
  ConfigLoader::modifyValue("Score", f[1].str(), score);
}

int Scoring::isInLadder(int score)
{
  int	best[Scoring::_max];
  int	count;

  count = 1;
  while (count < _max + 1)
    {
      std::stringstream s;
      s << "best_score_" << count;

      if (!ConfigLoader::keyExist("Score", s.str()))
	addScoreLine(count);
      ConfigLoader::getVarValue("Score", s.str(), best[count - 1]);
      ++count;
    }
  count = 1;
  while (count < _max + 1)
    {
      if (best[count - 1] < score)
	return (count);
      ++count;
    }
  return (0);
}

void Scoring::getScoreLine(int count, std::string &str, int &score)
{
  std::stringstream f[2];

  f[0] << "best_player_" << count;
  f[1] << "best_score_" << count;
  if (!ConfigLoader::keyExist("Score", f[0].str()) || !ConfigLoader::keyExist("Score", f[1].str()))
    addScoreLine(count);
  ConfigLoader::getVarValue("Score", f[0].str(), str);
  ConfigLoader::getVarValue("Score", f[1].str(), score);
}

void Scoring::addScore(int place, const std::string &name, int score)
{
  int	count;
  std::string n[2];
  int	s[2];
  bool	replace;

  count = 1;
  replace = false;
  s[0] = 0;
  while (count < _max + 1)
    {
      getScoreLine(count, n[0], s[0]);
      if (count == place)
	{
	  replace = true;
	  modifyValue(count, name, score);
	}
      else if (replace)
	modifyValue(count, n[1], s[1]);
      n[1] = n[0];
      s[1] = s[0];
      ++count;
    }
  ConfigLoader::writeToFile("Score.txt", "Score");
  ConfigLoader::dump();
}
