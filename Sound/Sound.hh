#ifndef SOUND_HH_
# define SOUND_HH_

# include	<string>
# include	<iostream>
# include	<vector>
# include	<SFML/Audio.hpp>

/**
**@class Zik
**@brief This class uses SFML audio to produce sounds and music into the projet
*/
class		Zik
{
public:

  /**
  **@enum SoundType
  **@brief The type of sound. Thanks sherlock.
  */
enum		SoundType
  {
    SOUND,
    MUSIC,
  };

  /**
   **@enum SoundTracks
   **@brief An enum to store the name of all sounds we can use
   */
enum		SoundTracks
  {
    SMOVESELECT,
    SCHANGEVAL,
    SSELECTION,
    CMDRETURN,
    GAMESTART,
    PAUSE,
    ITEMGET,
    PLAYEROUT,
    LIFEUP,
    KICKBOMB,
    NORMBOMB,
    SPIKEBOMB,
  };

  /**
   **@enum MusicTracks
   **@brief An enum to store the name of all musics we can use
   */
enum		MusicTracks
  {
    MENU,
    MOVESELECT,
    CHANGEVALUP,
    CHANGEVALDOWN,
    SELECTION,
    INGAME,
  };

private:
  /**
   **@var names
   **@brief names is a simple vector of strings to store the names of the sounds
   */
  std::vector<std::string>	names;

  /**
   **@var Musics
   **@brief Musics is a simple vector of sf::Music * used to store the musics to be called later
   */
  std::vector<sf::Music *>	Musics;

  /**
   **@var Sounds
   **@brief is a simple vector of sf::Sound * used to store the sounds to be called later
   */
  std::vector<sf::Sound *>	Sounds;

public:
  Zik();
  ~Zik();

  /**
   * @brief a necessary evil to catch the exception Zik could throw
   */
  void		initialize();

  /**
   **@param type variable, from the same enum, to play a sound
   **@brief this function is used to play sounds
   */
  void		zPlay(SoundTracks type);

  /**
   **@param type variable, from the same enum, to play a music
   **@param loop a bool to play the music into a loop or not
   **@brief this function is used to play musics
   */
  void		zPlay(MusicTracks type, bool loop);

  /**
   **@fn zPause
   **@brief the name speaks for itself
   */
  void		zPause(MusicTracks);

  /**
   **@fn zStop
   **@brief the name speaks for itself
   */
  void		zStop(MusicTracks);

  /**
   **@fn fillNames
   **@brief a function to put the names of the sounds into vectors
   */
  void		fillNames();
};

#endif
