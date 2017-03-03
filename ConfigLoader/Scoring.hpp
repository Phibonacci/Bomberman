#ifndef SCORING_HPP_
# define SCORING_HPP_

# include "ConfigLoader.hpp"

/**
 ** this class generates all the scores
 ** @brief Generate the scoring file for players
 */
class Scoring
{
public:
  Scoring();
  ~Scoring();

private:
  static int _max;
  static bool _init;

public:
  /**
   ** This function verify if the score can enter in the bests scores
   ** @param score
   */
  static int isInLadder(int);

  /**
   ** This function adds the score in the place passed as parameter with the login and score
   ** @param place
   ** @param name
   ** @param score
   */
  static void addScore(int, const std::string &, int);

  /**
   ** This function takes in parameter the number of high score slots
   ** @param max
   */
  static void initialize(int);

  /**
   ** This function adds empty lines to the Score file
   ** @param count
   */
  static void addScoreLine(int);

  /**
   ** This function modify the line of the index count with the new login and new score
   ** @param count
   ** @param name
   ** @param score
   */
  static void modifyValue(int, const std::string &, int);

  /**
   ** This function returns the score at the index count
   ** @param count
   ** @param str
   ** @param score
   */
  static void getScoreLine(int, std::string &, int &);
};

#endif
