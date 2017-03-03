#include <iostream>
#include <stdexcept>
#include "MasterController.hpp"
#include "Except.hpp"

size_t Controller::MasterController::_cuse = 0;
size_t Controller::MasterController::_cmax = 0;
std::vector<Controller::Peripheral*> Controller::MasterController::_tabPeriph;

void	Controller::MasterController::initialize()
{
  _cuse = 0;
  try
    {
      while (true)
	{
	  _tabPeriph.push_back(new Peripheral(_cmax, 10000));
	  _cmax++;
	}
    }
  catch (ExceptController& e)
    {}
}

Controller::Peripheral*	Controller::MasterController::rtPeripheral()
{
  if (_cuse == _cmax)
    return (NULL);
  return (_tabPeriph[_cuse++]);
}

void		Controller::MasterController::restart()
{
  _cuse = 0;
}

int		Controller::MasterController::getNController()
{
  return _tabPeriph.size();
}
