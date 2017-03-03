#include <iostream>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include "Except.hpp"

#include "Sound.hh"

void		Zik::fillNames()
{
  this->names.push_back("assets/Sound/mgamewav.wav");
  this->names.push_back("assets/Sound/mchangevalup.wav");
  this->names.push_back("assets/Sound/mchangevaldown.wav");
  this->names.push_back("assets/Sound/mmoveselect.wav");
  this->names.push_back("assets/Sound/mselection.wav");
  this->names.push_back("assets/Sound/smoveselect.wav");
  this->names.push_back("assets/Sound/schangeval.wav");
  this->names.push_back("assets/Sound/sselection.wav");
  this->names.push_back("assets/Sound/scmdreturn.wav");
  this->names.push_back("assets/Sound/sgamestart.wav");
  this->names.push_back("assets/Sound/spause.wav");
  this->names.push_back("assets/Sound/sitemget.wav");
  this->names.push_back("assets/Sound/splayerout.wav");
  this->names.push_back("assets/Sound/slifeup.wav");
  this->names.push_back("assets/Sound/skickbomb.wav");
  this->names.push_back("assets/Sound/snormbomb.wav");
  this->names.push_back("assets/Sound/sspikebomb.wav");
  this->names.push_back("assets/Sound/mfinalgame.wav");
}

Zik::Zik()
{
}

void	Zik::initialize() {
  std::vector<std::string>::iterator	it;
  std::string a;

  fillNames();
  it = names.begin();
  while (it != names.end())
    {
      a = *it;
      if (a[13] == 'm')
	{
	  sf::Music		*muz = new sf::Music;

	  if (!muz->openFromFile(a))
	    throw ExceptSound();
	  else
	    {
	      this->Musics.push_back(muz);
	    }
	}
      else if (a[13] == 's')
	{
	  sf::SoundBuffer *buffer = new sf::SoundBuffer;
	  sf::Sound	*sound = new sf::Sound;

	  if (!buffer->loadFromFile(a))
	    throw ExceptSound();
	  else
	    {
	      sound->setBuffer(*buffer);
	      this->Sounds.push_back(sound);
	    }
	}
      ++it;
    } 
}

Zik::~Zik()
{
  std::vector<sf::Music *>::iterator	it;

  it = this->Musics.begin();
  while (it != Musics.end())
    {
      delete *it;
      ++it;
    }
}

void			Zik::zPlay(SoundTracks type)
{
  Sounds[type]->play();
}

void			Zik::zPlay(MusicTracks type, bool loop)
{
  Musics[type]->play();
  Musics[type]->setLoop(loop);
}

void			Zik::zPause(MusicTracks type)
{
  Musics[type]->pause();
}

void			Zik::zStop(MusicTracks type)
{
  Musics[type]->stop();
}
