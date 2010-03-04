/** @file CMouseObserver.cpp
* @author Rafal Malinowski
* @date 2009.01.07
* @version 0.6
* @brief klasa CMouseObserver jest abstrakcyjna klasa po ktorej beda dziedziczyc wszystkie klasy zainteresowane obsluga myszy
*	
*		
*/

#include "CMouseObserver.hpp"
int CMouseObserver::obs_counter_=1;

void CMouseObserver::setMoveObserver (bool x)
{
	if(x) moveObserver_=true;
	else moveObserver_=false;
}

bool CMouseObserver::getMoveObserver()
{
	return moveObserver_;
}

void CMouseObserver::setId()
{
	id_=obs_counter_;
	obs_counter_++;
}

void CMouseObserver::setMoveIsOver (bool x)
{
	mouseIsOver_= x;
}

bool CMouseObserver::getMoveIsOver()
{
	return mouseIsOver_;
}
/// destruktor wirutalny
CMouseObserver::~CMouseObserver()
{
	std::cout<<"CMouseObserver::~CMouseObserver: niszczenie"<<std::endl; 
		
}

//~~CMouseObserver.cpp
