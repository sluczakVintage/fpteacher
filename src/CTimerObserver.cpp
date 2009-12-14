#include "CTimerObserver.hpp"

CTimerObserver::~CTimerObserver()
{
	std::cout<<"CTimerObserver::~CTimerObserver: niszczenie"<<std::endl; 
	CTimer::getInstance()->removeObserver(*this);
		
}