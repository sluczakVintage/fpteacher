/** @file CMouseObserver.cpp
* @author Rafal Malinowski
* @date 2009.01.07
* @version 0.1_draft
* @brief klasa CMouseObserver jest abstrakcyjna klasa po ktorej beda dziedziczyc wszystkie klasy zainteresowane obsluga myszy
*	
*		
*/

#include "CMouseObserver.hpp"


/// destruktor wirutalny
CMouseObserver::~CMouseObserver()
{
	std::cout<<"CMouseObserver::~CMouseObserver: niszczenie"<<std::endl; 
		
}

//~~CMouseObserver.cpp