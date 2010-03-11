/** @file CKeyObserver.cpp
* @author Rafal Malinowski
* @date 2009.01.07
* @version 0.6
* @class CKeyObserver CKeyObserver.hpp
* @brief klasa CKeyObserver jest abstrakcyjna klasa po ktorej beda dziedziczyc wszystkie klasy zainteresowane obsluga klawiatury
*	
*		
*/

#include "CKeyObserver.hpp"
using namespace logging;

int CKeyObserver::obsCounter_=0;

CKeyObserver::CKeyObserver()
{
	id_=obsCounter_;
	obsCounter_++;
}

int CKeyObserver::getId() const
{
	return id_;
}

int CKeyObserver::getCounter() const
{
	return obsCounter_;
}
//~~CKeyObserver.cpp
