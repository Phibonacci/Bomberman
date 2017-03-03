#ifndef ASCREEN_H_
# define ASCREEN_H_

# include "ACamera.hh"
# include "ASubScreen.hh"
# include <list>
# include <vector>
# include <BasicShader.hh>

# define SCREENX	1920
# define SCREENY	1080

/**
 **@namespace Screen
 **@brief Namespace for the screen operations
 */
namespace Screen
{
  /**
   **@class AScreen
   **@brief a class to manipulate the screen
   */
  class	AScreen
  {
  private:
    /**
     **@class inScreen
     **@brief in da place to deal with what's in the screen
     */
    class	inScreen
    {
      /**
       **@var _pos3d
       **@brief player pos
       */
      glm::vec3 const& _pos3d;

      /**
       **@var _size3d
       **@brief size of the screen
       */
      glm::vec3 const& _size3d;

      /**
       **@var _store
       **@brief list of sub screens
       */
      std::list<ASubScreen*> *_store;
    public:

      /**
       **@fn inScreen
       **@brief manage stuff in the screen
       */
      inScreen(glm::vec3 const&, glm::vec3 const&, std::list<ASubScreen*> *);
      bool	operator()(ASubScreen *);
    };

    /**
     **@class Updater
     **@brief Update ALL the things!
     */
    class	Updater
    {
    public:
      Updater() {}
      void	operator()(ASubScreen *);
    };
  private:
    /**
     **@var _shader
     **@brief teh shaderz
     */
    gdl::BasicShader		_shader;

    /**
     **@var _screens
     **@brief teh skreens
     */
    std::vector<ASubScreen*>	_screens;

    /**
     **@var _inScreens
     **@brief teh kontentz of teh skreenz
     */
    std::list<ASubScreen*>	_inScreens;
  public:
    AScreen();

    /**
     **@fn initialize
     **@brief read the title
     */
    bool	initialize();

    /**
     **@fn isInAnyScreen
     **@brief is it seriously not enough clear for you?
     */
    bool	isInAnyScreen(glm::vec3 const&, glm::vec3 const&) const;

    /**
     **@fn initScreensIn
     **@brief it inits screens in
     */
    void	initScreensIn(glm::vec3 const&, glm::vec3 const&);

    /**
     **@fn getShader
     **@brief gets the shader
     */
    gdl::AShader &getShader() {return _shader;}

    /**
     **@fn addScreen
     **@brief adds a creen
     */
    bool	addScreen(ASubScreen *);

    /**
     **@fn update
     **@brief OH COME ON
     */
    void	update();

    /**
     **@fn reset
     **@brief resets the screen
     */
    void	reset();

    /**
     **@fn cleanScreens
     **@brief come on you can do it
     */
    void	cleanScreens();
    std::vector<ASubScreen*> const&		getScreens() const {return _screens;}

    /**
     **@fn inBegin
     **@brief thos function does stuff at the beginning
     */
    std::list<ASubScreen*>::const_iterator	inBegin() const {return _inScreens.begin();}

    /**
     **@fn inEnd
     **@brief this function does stuff at the end
     */
    std::list<ASubScreen*>::const_iterator	inEnd() const  {return _inScreens.end();}
    ~AScreen();
  };
};
#endif /* !ASCREEN_H_ */
