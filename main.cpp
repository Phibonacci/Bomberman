#include <iostream>
#include "GameEngine.hh"
#include "Except.hpp"

int		main()
{
  try
    {
      GameEngine	engine;

      if (engine.initialize() != true)
	return (1);
      while (engine.update() == true)
	engine.draw();
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  return EXIT_SUCCESS;
}
