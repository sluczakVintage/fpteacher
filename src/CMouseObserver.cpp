#include "CMouseObserver.hpp"


CMouseObserver::~CMouseObserver()
{
	std::cout<<"CMouseObserver::~CMouseObserver: niszczenie"<<std::endl; 
	//CMouse::getInstance()->removeObserver(*this);
		
}